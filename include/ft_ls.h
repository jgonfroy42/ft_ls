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
# include <errno.h>
# include <sys/sysmacros.h>
# include <sys/xattr.h>

# define LEN_LINKS len_col[0]
# define LEN_OWNER len_col[1]
# define LEN_GROUP len_col[2]
# define LEN_SIZE len_col[3]
# define LEN_DEV_MAJ len_col[4]

# define l_flag 1 << 0
# define R_flag 1 << 1
# define a_flag 1 << 2
# define r_flag 1 << 3
# define t_flag 1 << 4
# define d_flag 1 << 5
# define one_flag 1 << 6
# define VALID_FLAGS "lRartd1" 

typedef struct	time
{
	char	*month;
	int	day;
	int	hour;
	
	int	seconds;
	int	minutes;
	int	year;
	bool	old;
}	t_time;

typedef struct s_file
{
	char		*path;
	char		perm[11];
	char		xattr;
	unsigned int	nb_links;
	char		*owner;
	char		*group;
	unsigned int	size;
	unsigned int	dev_major;
	unsigned int	dev_minor;
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
 * parsed arguments
 */

	int8_t	flags;
	
	bool			invalid_path;
	struct s_list_files	*list_dir;
	struct s_list_files	*list_not_dir;

/*
 * needed for column display
 */
	size_t	len_col[5];

/*
 * for -R option
 */
	struct	s_list_files	*recursion;
	bool	recursion_call;

}	t_args;


/*
 * parsing.c
 */

t_file	*init_file();
t_file	*create_new_file(struct stat buffer, int flags);
void	add_file(t_args *parsed_args, char *path);
int	parse_args(t_args *parsed_args, char **args);
t_time	convert_time(char *stime);


/*
 * utils_list.c
 */
void	del_file_list(void *elem);
void	del_elem(void *elem);
t_list_files	*copy_list(t_list_files *src);

/*
 * ft_ls.c
 */

void	ft_ls(t_args *args);

/*
 * test.c
 */
void	tests(t_args *args);
void	display_list(void *file);
void	display_owners(void *file);

/*
 * sorting.c
 */

void	sorting_file(t_args *args, t_list_files **files);

/*
 * handle_error.c
 */

void	print_error(char *problem, char *path, char *strerr);

#endif
