/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put*.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dancel <dancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:11:32 by dancel            #+#    #+#             */
/*   Updated: 2024/11/11 20:55:12 by dancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *str)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	if (!str)
		str = "(null)";
	while (str[i])
		i++;
	len += write(1, str, i);
	return (len);
}

int	ft_putptr(void *ptr)
{
	unsigned long long	ull;

	ull = (unsigned long long)ptr;
	if (!ull)
		return (write(1, "(nil)", 5));
	write(1, "0x", 2);
	return (ft_puthex(ull, 'x') + 2);
}

int	ft_putnbr(int n)
{
	char	c;
	int		len;
	long	num;

	len = 0;
	num = n;
	if (num < 0)
	{
		len += write(1, "-", 1);
		num = -num;
	}
	if (num >= 10)
		len += ft_putnbr(num / 10);
	c = (num % 10) + '0';
	len += write(1, &c, 1);
	return (len);
}

int	ft_putnbr_unsigned(unsigned int n)
{
	char	c;
	int		len;

	len = 0;
	if (n >= 10)
		len += ft_putnbr_unsigned(n / 10);
	c = (n % 10) + '0';
	len += write(1, &c, 1);
	return (len);
}

int	ft_puthex(unsigned long long num, char format)
{
	char			*hex;
	int				len;

	len = 0;
	if (format == 'x')
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
	if (num >= 16)
		len += ft_puthex(num / 16, format);
	len += write(1, &hex[num % 16], 1);
	return (len);
}
