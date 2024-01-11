#include "../include/ft_ls.h"

void	del_file_list(void *elem)
{
	if (((t_file *)elem)->date.month != NULL)
		free(((t_file*)elem)->date.month);
	if (((t_file *)elem)->path)
		free(((t_file *)elem)->path);
	if (((t_file *)elem)->owner)
		free(((t_file *)elem)->owner);
	if (((t_file *)elem)->group)
		free(((t_file *)elem)->group);
	free(elem);
}

void	del_path_list(void *elem)
{
/*
 * You do nothing Jonh Snow
 */
	(void)elem;
}
