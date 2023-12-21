/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 16:55:26 by jgonfroy          #+#    #+#             */
/*   Updated: 2020/01/14 18:55:39 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/ft_printf.h"

t_flags	check_flags(t_flags format)
{
	if (format.width < 0)
	{
		format.minus = 1;
		format.width = -format.width;
	}
	if (format.minus == 1 && format.zero == 1)
		format.zero = 0;
	if (format.precision < 0)
		format.precision = -1;
	return (format);
}

t_flags	get_precision(t_flags format, char *str, va_list ap)
{
	if (*str == '.')
		format.precision = 0;
	str++;
	if (*str == '*')
		format.precision = (va_arg(ap, int));
	else
	{
		while (ft_isdigit(*str))
		{
			format.precision = format.precision * 10 + (*str - 48);
			str++;
		}
	}
	return (format);
}

t_flags	get_flags(t_flags format, char *str, va_list ap)
{
	while (*str == '-' || *str == '0')
	{
		if (*str == '-')
			format.minus = 1;
		if (*str == '0')
			format.zero = 1;
		str++;
	}
	if (*str == '*')
	{
		format.width = (va_arg(ap, int));
		str++;
	}
	else
	{
		while (ft_isdigit(*str))
		{
			format.width = format.width * 10 + (*str - 48);
			str++;
		}
	}
	return (check_flags(get_precision(format, str, ap)));
}

int		write_arg(t_flags format, va_list ap)
{
	if (format.type == '%')
		format.size = conv_pct(format);
	else if (ft_charset(format.type, TYPE) == 0)
		format.size = conv_char(format.type, format);
	else if (format.type == 'c')
		format.size = conv_char(va_arg(ap, int), format);
	else if (format.type == 's')
		format.size = conv_str(va_arg(ap, char *), format);
	else if (format.type == 'd' || format.type == 'i')
		format.size = conv_integer(va_arg(ap, int), format);
	else if (format.type == 'p')
		format.size = conv_unsigned(va_arg(ap, unsigned long), format);
	else if (ft_charset(format.type, TYPE))
		format.size = conv_unsigned(va_arg(ap, unsigned int), format);
	return (format.size);
}
