#ifndef FT_LS_H
# define FT_LS_H

# include "./../ft_printf/includes/ft_printf.h"

# include <stdio.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <unistd.h>
# include <dirent.h>
# include <string.h>
# include <stdlib.h>


typedef struct	time
{
	char	*month;
	int	day;
	int	hour;
	int	minutes;
	int	year;

}	t_time;

typedef struct s_file
{
	char		*path;
	char		perm[10];
	unsigned int	nb_links;
	char		*owner;
	char		*group;
	unsigned int	size;
	t_time		date;

}	t_file;

typedef struct	s_list_files
{
	struct s_file		*file;
	struct s_list_files	*next;

}	t_list_files;

typedef struct	s_list_raw_args
{
	char	*path;
	struct s_list_raw_args	*next;
}	t_list_raw_args;

typedef struct	s_args
{

/*
 * cmd options
 */
	const char	*valid;

	bool	l;
	bool	R;
	bool	a;
	bool	r;
	bool	t;


/*
 * cmd arguments
 */
	struct s_list_files	*list_dir;
	struct s_list_files	*list_not_dir;

/*
 * needed for colmun display
 */
	size_t	length_col_owner;
	size_t	length_col_group;
	size_t	length_col_size;

}	t_args;


/*
 * parsing.c
 */

t_file	*create_new_file(struct stat buffer, bool l, bool t);
int	add_file(t_args *parsed_args, char *path);
int	parse_args(t_args *parsed_args, char **args);
t_time	convert_time(char *stime);


/*
 * utils_list.c
 */
void	del_file_list(void *elem);
void	del_path_list(void *elem);

/*
 * ft_ls.c
 */

void	ft_ls(t_args *args);

/*
 * test.c
 */
void	tests(t_args *args);
void	display_list(void *file);

/**
 * sorting.c
 */

void	sorting_file(t_args *args, t_list_files **files);

#endif
