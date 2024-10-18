/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 17:32:07 by jgonfroy          #+#    #+#             */
/*   Updated: 2020/01/14 18:38:46 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/ft_printf.h"

int	conv_pct(t_flags format)
{
	int i;

	i = 0;
	if (format.zero == 1)
	{
		while (i < format.width - 1)
		{
			write(1, "0", 1);
			i++;
		}
		write(1, "%", 1);
		return (format.size + i + 1);
	}
	if (format.minus == 1)
		write(1, "%", 1);
	while (i < format.width - 1)
	{
		write(1, " ", 1);
		i++;
	}
	if (format.minus == 0)
		write(1, "%", 1);
	return (format.size + i + 1);
}

int	conv_char(int c, t_flags format)
{
	int i;

	i = 0;
	if (format.minus == 1)
		ft_putchar_fd(c, 1);
	while (i < format.width - 1)
	{
		write(1, " ", 1);
		i++;
	}
	if (format.minus == 0)
		ft_putchar_fd(c, 1);
	format.size = format.size + i + 1;
	return (format.size);
}

int	conv_str(char *s, t_flags format)
{
	int i;
	int size;

	i = 0;
	if (s == NULL)
		s = ft_strdup("(null)");
	else if (format.precision != -1)
		s = ft_substr(s, 0, format.precision);
	else
		s = ft_strdup(s);
	size = ft_strlen(s);
	if (format.minus == 1)
		ft_putstr_fd(s, 1);
	while (i < format.width - size)
	{
		write(1, " ", 1);
		i++;
	}
	if (format.minus == 0)
		ft_putstr_fd(s, 1);
	format.size = format.size + i + size;
	free(s);
	return (format.size);
}

int	conv_integer(int n, t_flags format)
{
	int size;
	int i;

	i = 0;
	size = size_int(n);
	if (format.precision >= size)
	{
		size = format.precision;
		if (n < 0 && size++)
			format.precision++;
	}
	else if (format.precision == -1 && format.zero == 1 && format.width > size)
		size = format.width;
	if (n == 0 && format.precision == 0)
		i = no_zero(format, size);
	else if (format.precision != -1)
		i = putnbr_flags(n, format, format.precision, size);
	else
	{
		if (format.minus == 0 && format.zero == 1)
			putnbr_precision(n, format.width);
		else
			i = putnbr_flags(n, format, format.precision, size);
	}
	return (format.size + i + size);
}

int	conv_unsigned(unsigned long n, t_flags format)
{
	int	size;
	int	i;

	i = 0;
	size = size_unsigned(n, format.type);
	if (format.precision > size)
	{
		size = format.precision;
		if (format.type == 'p')
			format.size = format.size + 2;
	}
	else if (format.precision == -1 && format.zero == 1 && format.width > size)
		size = format.width;
	if (n == 0 && format.precision == 0)
		i = no_zero(format, size);
	else if (format.precision != -1)
		i = putunsigned_flags(n, format, format.precision, size);
	else
	{
		if (format.minus == 0 && format.zero == 1)
			putunsigned_precision(n, format.width, format.type);
		else
			i = putunsigned_flags(n, format, format.precision, size);
	}
	return (format.size + i + size);
}
