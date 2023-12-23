#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>
# include <sys/stat.h>
# include <stdbool.h>
# include "./../ft_printf/includes/ft_printf.h"
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>

typedef struct s_file
{
	char		*path;
	char		perm[10];
	unsigned int	nb_links;
	char		*owner;
	char		*group;
	unsigned int	size;
	char		*date;

}	t_file;

typedef struct	s_list_files
{
	struct s_file		*file;
	struct s_list_files	*next;

}	t_list_files;

typedef struct	s_args
{
	const char	*valid;

	bool	l;
	bool	R;
	bool	a;
	bool	r;
	bool	t;

	struct s_list_files	*list_dir;
	struct s_list_files	*list_not_dir;

}	t_args;


/*
 * parsing.c
 */

int	parse_args(t_args *parsed_args, char **args);


/*
 * utils_list.c
 */
void	del_file_list(void *elem);

/*
 * ft_ls.c
 */

void	ft_ls(t_args *args);

#endif
