/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   annexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 16:52:20 by jgonfroy          #+#    #+#             */
/*   Updated: 2020/01/14 18:42:14 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/ft_printf.h"

void	ft_putnbr_base(unsigned long n, char *base)
{
	if (n < ft_strlen(base))
		ft_putchar_fd(base[n], 1);
	else
	{
		ft_putnbr_base(n / ft_strlen(base), base);
		ft_putchar_fd(base[n % ft_strlen(base)], 1);
	}
}

int		size_int(int n)
{
	int size;

	size = 1;
	if (n < 0)
		size++;
	while (n / 10 != 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

int		size_unsigned(unsigned long n, char type)
{
	int size;
	int base_size;

	if (type == 'u')
		base_size = 10;
	else
		base_size = 16;
	size = 1;
	while (n / base_size != 0)
	{
		n = n / base_size;
		size++;
	}
	if (type == 'p')
		size += 2;
	return (size);
}

t_flags	ft_reset(t_flags format)
{
	format.minus = 0;
	format.zero = 0;
	format.width = 0;
	format.precision = -1;
	format.type = 0;
	return (format);
}
