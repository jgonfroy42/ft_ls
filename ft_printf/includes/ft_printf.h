/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:55:09 by jgonfroy          #+#    #+#             */
/*   Updated: 2020/01/14 18:51:45 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "./../libft/libft.h"
# include <stdarg.h>
# include <unistd.h>

# define TYPE	"cspdiuxX%"
# define FLAG	"-0.*123456789"
# define ALL	"-0.*cspdiuxX%123456789"

/*
** Declaration structure
*/

typedef	struct	s_flags
{
	int			size;
	int			incr;
	int			minus;
	int			zero;
	int			width;
	int			precision;
	char		type;

}				t_flags;


int		ft_printf(const char *str, ...);

/*
** Fonctions conversion.c
*/

int				conv_char(int c, t_flags format);
int				conv_pct(t_flags format);
int				conv_str(char *s, t_flags format);
int				conv_integer(int n, t_flags format);
int				conv_unsigned(unsigned long n, t_flags format);

/*
** annexes.c
*/

void			ft_putnbr_base(unsigned long n, char *base);
int				size_int(int n);
int				size_unsigned(unsigned long n, char type);
t_flags			ft_reset(t_flags format);

/*
** Fonctions nbr_flags.c
*/

void			putnbr_precision(int n, int precision);
int				putnbr_flags(int n, t_flags format, int precision, int size);
void			putunsigned_precision(unsigned long n, int precision,
		char type);
int				putunsigned_flags(unsigned long n, t_flags format,
		int precision, int size);
int				no_zero(t_flags fornat, int size);

/*
** Fonctions ft_printf.c
*/

t_flags			ft_parse(t_flags format, const char *str, va_list ap);
int				ft_string(t_flags format, const char *str, va_list ap);
int				ft_printf(const char *str, ...);

/*
** Fonctions flags.c
*/
t_flags			check_flags(t_flags format);
t_flags			get_flags(t_flags format, char *str, va_list ap);
t_flags			get_precision(t_flags format, char *str, va_list ap);
int				write_arg(t_flags format, va_list ap);

#endif
