/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancel <dancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:27:09 by dancel            #+#    #+#             */
/*   Updated: 2024/11/17 16:24:16 by dancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_octet	g_octet = {0, 0, 0, NULL};

void	handle_sigusr(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (g_octet.client_pid == 0)
		g_octet.client_pid = info->si_pid;
	if (sig == SIGUSR1)
		g_octet.current_char = (g_octet.current_char << 1);
	else if (sig == SIGUSR2)
		g_octet.current_char = (g_octet.current_char << 1) | 1;
	g_octet.bit_count++;
	if (kill(g_octet.client_pid, SIGUSR1) == -1)
	{
		ft_printf("Error: failed to send acknowledgment to client.\n");
		g_octet.client_pid = 0;
		free(g_octet.string);
		g_octet.string = NULL;
		exit(1);
	}
	if (g_octet.bit_count == 8)
		ft_make_string();
}

void	ft_make_string(void)
{
	if (g_octet.current_char == '\0')
	{
		ft_printf("%s\n", g_octet.string);
		g_octet.client_pid = 0;
		free(g_octet.string);
		g_octet.string = NULL;
	}
	else
	{
		g_octet.string = ft_join_mt(g_octet.string, (char)g_octet.current_char);
		if (!g_octet.string)
		{
			g_octet.client_pid = 0;
			free(g_octet.string);
			g_octet.string = NULL;
			exit(1);
		}
	}
	g_octet.bit_count = 0;
	g_octet.current_char = 0;
}

char	*ft_join_mt(char *s1, char c)
{
	char	*new_str;
	int		i;
	int		len_str;

	if (!s1)
		len_str = 0;
	else
		len_str = ft_strlen(s1);
	new_str = malloc(len_str + 2);
	if (!new_str)
		return (NULL);
	i = -1;
	while (++i < len_str)
		new_str[i] = s1[i];
	new_str[i] = c;
	new_str[i + 1] = '\0';
	free(s1);
	s1 = NULL;
	return (new_str);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	main(void)
{
	struct sigaction	sa;
	sigset_t			sigmask;

	ft_printf("<< Server PID: %d >>\n\n", getpid());
	sigemptyset(&sigmask);
	sigaddset(&sigmask, SIGUSR1);
	sigaddset(&sigmask, SIGUSR2);
	sa.sa_sigaction = handle_sigusr;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_mask = sigmask;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_printf("Error: failed to set signal handlers.\n");
		exit(1);
	}
	while (1)
		pause();
	return (0);
}
