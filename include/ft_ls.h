#ifndef FT_LS_H
# define FT_LS_H

# include "./../ft_printf/includes/ft_printf.h"

typedef struct	s_args
{
	bool	l = false;
	bool	R = false;
	bool	a = false;
	bool	r = false;
	bool	t = false;

	char	*valid = "lRart"
}	t_args;


typedef struct	s_paths
{
	char	*path;
	struct s_paths	*next;
}	t_paths;

#endif
