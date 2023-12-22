/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 16:55:26 by jgonfroy          #+#    #+#             */
/*   Updated: 2020/01/14 18:55:39 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/ft_printf.h"

t_flags	ft_parse(t_flags format, const char *str, va_list ap)
{
	char	*s_flags;
	int		start;

	start = format.incr;
	while (str[format.incr] && (ft_charset(str[format.incr], FLAG)))
		format.incr++;
	s_flags = ft_substr(str, start, format.incr - start);
	if (!str[format.incr])
		return (format);
	else
	{
		format = get_flags(format, s_flags, ap);
		format.type = str[format.incr];
	}
	free(s_flags);
	format.incr++;
	format.size = write_arg(format, ap);
	format = ft_reset(format);
	return (format);
}

int		ft_string(t_flags format, const char *str, va_list ap)
{
	while (str[format.incr])
	{
		while (str[format.incr] && str[format.incr] != '%')
		{
			ft_putchar_fd(str[format.incr], 1);
			format.size++;
			format.incr++;
		}
		if (str[format.incr] == '%')
		{
			format.incr++;
			if (str[format.incr] && ft_charset(str[format.incr], ALL))
				format = ft_parse(format, str, ap);
		}
	}
	return (format.size);
}

int		ft_printf(const char *str, ...)
{
	va_list ap;
	t_flags format;

	format.size = 0;
	format.incr = 0;
	va_start(ap, str);
	format = ft_reset(format);
	format.size = ft_string(format, str, ap);
	va_end(ap);
	return (format.size);
}
