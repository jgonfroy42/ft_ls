#include "../include/ft_ls.h"

void	del_file_list(void *elem)
{
	free(((t_file*)elem)->date.month);
	free(elem);
}

void	del_path_list(void *elem)
{
/*
 * You do nothing Jonh Snow
 */
	(void)elem;
}
