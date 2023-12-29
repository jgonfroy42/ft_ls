#include "../include/ft_ls.h"

/*
 * Préparation : si size list_dir == 0 && size list_not_dir == 0
 * 	add . à list_dir
 *
 * 1. on s'occupe des not_dir
 * 	a - on trie la liste en fonction de -t et -r.
 * 	ATTENTION fonction doit être utilisable par des dir et à d'autres moments du code
 * 	b - on affiche les infos en fonction de -l.
 * 	ATTENTION fonction doit être assez modulable pour l'affichage de l'intérieur des dossiers.
 *
 * 2. on s'attaque aux dir
 *	a - si not_dir : on saute une ligne
 * 	b - on trie la liste (même fonction qu'en 1. a)
 * 	c - on récupère la liste des files du dir
 * 	ATTENTION : on exclut ou non les fichiers cachés en fonction de -a.
 * 	+ si -l ou -t on ajoute les info nécessaires
 * 	d - on tri la liste obtenue
 * 	e - on affiche de la liste obtenue
 * 		1) si size list_dir == 1 && size list_not_dir == 0
 * 			on affiche pas le dossier concerné
 * 		sinon
 *			"{path}:\n" puis liste
 *		2) même fonction qu'en 1. b 
 *
 */
t_list_files	*get_dir_items(char *path, bool hidden)
{
	DIR *dir;
	struct dirent *entry;
	t_list_files	*ret;

	ret = NULL;
	if((dir = opendir(path)) == NULL)
	{
		ft_printf("cannot open directory: %s\n", dir);
		return ret;
	}

	while ((entry = readdir(dir)) != NULL)
	{
		if (!hidden && entry->d_name[0] == '.')
			continue;
		ft_printf("%s\n", entry->d_name);
	}
	closedir(dir);
	return ret ;
}

void	display_not_dir(t_list_files *list, bool l)
{
	int current_year;

	if (l)
	{
		time_t  seconds=time(NULL);
		struct tm       *current_time=localtime(&seconds);
		current_year = current_time->tm_year + 1900;
	}

	while(list)
	{	if (!l)
		{
			ft_printf("%s", list->file->path);
			if (list->next)
				ft_printf(" ");
			else
				ft_printf("\n");
		}
		else
		{
			ft_printf("%s. %d %s %s %d %s %d ", list->file->perm, list->file->nb_links, list->file->owner, list->file->group, list->file->size, list->file->date.month, list->file->date.day);

			if (list->file->date.year == current_year)
				ft_printf("%d:%d", list->file->date.hour, list->file->date.minutes);
			else
				ft_printf("%d", list->file->date.year);

			ft_printf(" %s\n", list->file->path);
		}
		list = list->next;
	}
}

void	ft_ls(t_args *args)
{
	t_list_files	*curr;

/*
 * no args so we display current dir
 */
	if (ft_lstsize((t_list *)args->list_dir) == 0 && ft_lstsize((t_list *)args->list_not_dir) == 0)
		add_file(args, ".");
	
	sorting_file(args, &args->list_not_dir);
	display_not_dir(args->list_not_dir, (args->l) ? true : false);		

	if (!args->list_dir)
		return ;

	if (args->list_not_dir)
		write(1, "\n", 1);

	curr = args->list_dir;
	while (curr)
	{
		get_dir_items(curr->file->path, args->a);		
		curr = curr->next;
	}
}
