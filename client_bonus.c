/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancel <dancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:17:23 by dancel            #+#    #+#             */
/*   Updated: 2024/11/17 17:17:26 by dancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static int	g_recepted = 0;

void	handle_ack(int sig)
{
	(void)sig;
	g_recepted = 1;
}

void	send_bit(int pid, char bit)
{
	int	time;

	time = 0;
	if (bit == 1)
	{
		if (kill(pid, SIGUSR2) == -1)
			ft_error_client(3);
	}
	else
	{
		if (kill(pid, SIGUSR1) == -1)
			ft_error_client(4);
	}
	while (!g_recepted && time < 3)
	{
		sleep(1);
		time++;
	}
	if (time == 3)
		ft_error_client(5);
	g_recepted = 0;
}

void	ft_error_client(int i)
{
	if (i == 0)
		ft_printf("Usage: <server_pid> <message>\n");
	if (i == 1)
		ft_printf("Invalid PID\n");
	if (i == 2)
		ft_printf("Error: failed to set acknowledgment signal handler.\n");
	if (i == 3)
		ft_printf("Error sending SIGURS2\n");
	if (i == 4)
		ft_printf("Error sending SIGURS1\n");
	if (i == 5)
		ft_printf("Time out\n");
	exit(1);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	s;
	int	nb;

	i = 0;
	s = 1;
	nb = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			s = -s;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		nb = nb * 10 + (nptr[i++] - '0');
	return (nb * s);
}

int	main(int argc, char *argv[])
{
	int	server_pid;
	int	i;
	int	j;

	if (argc != 3)
		ft_error_client(0);
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0 || !server_pid)
		ft_error_client(1);
	if (signal(SIGUSR1, handle_ack) == SIG_ERR)
		ft_error_client(2);
	i = -1;
	while (argv[2][++i])
	{
		j = 8;
		while (--j >= 0)
			send_bit(server_pid, ((argv[2][i] >> j) & 1) == 1);
	}
	j = 8;
	while (--j >= 0)
		send_bit(server_pid, 0);
	return (0);
}
