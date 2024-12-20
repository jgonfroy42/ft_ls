#include "../include/ft_ls.h"

void	display_list(void *file)
{
	ft_printf("elem :%s\n", ((t_file *)file)->path);
}

void	display_owners(void *file)
{
	ft_printf("-> File: %s\nOwner: %s\n\n", ((t_file *)file)->path, ((t_file *)file)->owner);
}


void	test_parsing(t_args *args)
{
/*
 * Affiche les options détectées dans le parsing et les chemins considérés comme valides
 */
	void	(*pfunc)(void *) = &display_list;

	ft_printf("flags: %d\n", args->flags);

	ft_printf("---TEST DU PARSING---\n\n");
	ft_printf("l : %i\na : %i\nR : %i\nr : %i\nt : %i\nd : %i\n1 : %i\n", (args->flags & l_flag) == l_flag, (args->flags & a_flag) == a_flag, (args->flags & R_flag) == R_flag, (args->flags & r_flag) == r_flag, (args->flags & t_flag) == t_flag, (args->flags & d_flag) == d_flag, (args->flags & one_flag) == one_flag);

	ft_printf("\nDirectory\n");
	ft_lstiter((t_list *)args->list_dir, pfunc);

	ft_printf("\nNot directory\n");
	ft_lstiter((t_list *)args->list_not_dir, pfunc);
}

void	test_permissions(t_args *args)
{
	ft_printf("\n---TEST PERMISSIONS---\n\n");

	t_list_files *list = args->list_not_dir;
	while (list)
	{
		ft_printf("%s %s\n", list->file->perm, list->file->path);
		list = list->next;
	}

	list = args->list_dir;
	while (list)
	{
		ft_printf("%s %s\n", list->file->perm, list->file->path);
		list = list->next;
	}

}

void	test_data(t_args *args)
{
	ft_printf("\n---TEST DATA---\n\n");

	t_list_files *list = args->list_not_dir;
	while (list)
	{
		ft_printf("%s. %d %s %s %d %s %d %d:%d %s\n", list->file->perm, list->file->nb_links, list->file->owner, list->file->group, list->file->size, list->file->date.month, list->file->date.day, list->file->date.hour, list->file->date.minutes, list->file->path);
		list = list->next;
	}

	list = args->list_dir;
	while (list)
	{
		ft_printf("%s. %d %s %s %d %s %d %d:%d %s\n", list->file->perm, list->file->nb_links, list->file->owner, list->file->group, list->file->size, list->file->date.month, list->file->date.day, list->file->date.hour, list->file->date.minutes, list->file->path);
		list = list->next;
	}
}

void	tests(t_args *args)
{
	test_parsing(args);
	test_permissions(args);
	test_data(args);
}
