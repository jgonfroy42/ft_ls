#include "../include/ft_ls.h"

/*
 * LS sans option
 * Préparation : si size list_dir == 0 && size list_not_dir == 0
 * 	add . à list_dir
 *
 * 1. on écrit la liste des not directory
 * 2. si dir not empty, on saute une ligne
 * 3. si size list_dir == 1 && size list_not_dir == 0
 * 	on display pas le dossier concerné
 * sinon
 *	display path + ":\n" puis liste
 *	si ~ on remplace par le chemin
 *
 */

void	display_not_dir(t_list_files *list, bool l)
{
	while(list)
	{	if (!l)
		{
			ft_printf("%s", list->file->path);
			if (list->next)
				ft_printf("\n");
		}
		else
			ft_printf("%s. %d %s %s %d %s %s\n", list->file->perm, list->file->nb_links, list->file->owner, list->file->group, list->file->size, list->file->date, list->file->path);
		list = list->next;
	}
	ft_printf("\n");
}

void	ft_ls(t_args *args)
{

/*
 * no args so we display current dir
 */

	if (ft_lstsize((t_list *)args->list_dir) == 0 && ft_lstsize((t_list *)args->list_not_dir) == 0)
		ft_lstadd_back((t_list **)&args->list_dir, ft_lstnew("."));

	display_not_dir(args->list_not_dir, (args->l) ? true : false);		
}
