#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>
# include <sys/stat.h>
# include <stdbool.h>
# include "./../ft_printf/includes/ft_printf.h"

typedef struct	s_paths
{
	char	*path;
	struct s_paths	*next;
}	t_paths;

typedef struct	s_args
{
	char	*valid;
	
	bool	l;
	bool	R;
	bool	a;
	bool	r;
	bool	t;

	struct s_paths	*list_paths;

}	t_args;


/*
 * parsing.c
*/

t_args	parse_args(char **args);

#endif
