/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 15:47:33 by jgonfroy          #+#    #+#             */
/*   Updated: 2020/01/14 18:41:45 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/ft_printf.h"

void	putnbr_precision(int n, int precision)
{
	int i;

	i = 0;
	if (n < 0)
	{
		write(1, "-", 1);
		if (n != -2147483648)
			n = -n;
		i++;
	}
	while (i < precision - size_int(n))
	{
		write(1, "0", 1);
		i++;
	}
	if (n == -2147483648)
		write(1, "2147483648", 10);
	else
		ft_putnbr_fd(n, 1);
}

int		putnbr_flags(int n, t_flags format, int precision, int size)
{
	int i;

	i = 0;
	if (format.minus == 1)
		putnbr_precision(n, precision);
	while (i < format.width - size)
	{
		write(1, " ", 1);
		i++;
	}
	if (format.minus == 0)
		putnbr_precision(n, precision);
	return (i);
}

void	putunsigned_precision(unsigned long n, int precision, char type)
{
	int		i;
	int		size;
	char	*base;

	i = 0;
	if (type == 'p')
		write(1, "0x", 2);
	if (type == 'u')
		base = "0123456789";
	else if (type == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	size = size_unsigned(n, type);
	if (type == 'p')
		size -= 2;
	while (i < precision - size)
	{
		write(1, "0", 1);
		i++;
	}
	ft_putnbr_base(n, base);
}

int		putunsigned_flags(unsigned long n, t_flags format, int precision,
		int size)
{
	int i;

	i = 0;
	if (format.minus == 1)
		putunsigned_precision(n, precision, format.type);
	while (i < format.width - size)
	{
		write(1, " ", 1);
		i++;
	}
	if (format.minus == 0)
		putunsigned_precision(n, precision, format.type);
	return (i);
}

int		no_zero(t_flags format, int size)
{
	int i;

	i = 0;
	size--;
	if (format.minus == 1 && format.type == 'p')
	{
		write(1, "0x", 2);
		size -= 2;
	}
	while (i < format.width - size)
	{
		write(1, " ", 1);
		i++;
	}
	if (format.minus == 0 && format.type == 'p')
		write(1, "0x", 2);
	return (i - 1);
}
