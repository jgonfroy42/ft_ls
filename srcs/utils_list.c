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

//possibilité de remplacer le pointeur sur function par NULL ?
void	del_elem(void *elem)
{
/*
 * You do nothing Jonh Snow
 */
	(void)elem;
}

void	*copy_file_elem(void *elem)
{
	t_file	*file;

	file = init_file();
	file->path = ft_strdup(((t_file*)elem)->path);
	return file;
}

t_list_files	*copy_list(t_list_files *src)
{
	return (t_list_files *)ft_lstmap((t_list*)src, copy_file_elem, del_elem);
}
