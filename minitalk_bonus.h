/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancel <dancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:17:01 by dancel            #+#    #+#             */
/*   Updated: 2024/11/17 17:17:03 by dancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <signal.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

typedef struct s_octet
{
	int			bit_count;
	int			current_char;
	int			client_pid;
	char		*string;
}				t_octet;

void	handle_ack(int sig);
void	send_bit(int pid, char bit);
void	ft_error_client(int i);
int		ft_atoi(const char *nptr);

void	handle_sigusr(int sig, siginfo_t *info, void *context);
void	ft_make_string(void);
char	*ft_join_mt(char *s1, char c);
size_t	ft_strlen(const char *s);

int		ft_printf(const char *format, ...);
int		ft_puthex(unsigned long long num, char format);
int		ft_putnbr_unsigned(unsigned int n);
int		ft_putnbr(int n);
int		ft_putptr(void *ptr);
int		ft_putstr(char *str);
int		ft_putchar(char c);
int		ft_printf_format(const char *format, int i, va_list args);

#endif
