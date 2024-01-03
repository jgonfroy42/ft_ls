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

long int	add_dir_files(t_list_files **list_files, t_args *args, char *dir_path, char *path)
{
	struct	stat buffer;
	t_file	*file;
	char *real_path;

	real_path = ft_strjoin(dir_path, path);
	if (args->l || args->t)
	{
		if (lstat(real_path, &buffer) != 0)
		{
			ft_printf("ls: cannot access '%s': %s\n", path, strerror(errno));
			free(dir_path);
			free(real_path);
			return 0;
		}
		file = create_new_file(buffer, args->l, args->t);
	}
	else
	{
		file = (t_file *)malloc(sizeof(t_file));
		file->date.month = NULL;
	}
	file->path = path;
	ft_lstadd_back((t_list **)list_files, ft_lstnew(file));

	free(dir_path);
	free(real_path);

	if (args->l)
		return buffer.st_blocks / 2;
	return 0;
}

int	get_dir_files(t_args *args, t_list_files **files, char *path)
{
	DIR *dir;
	struct dirent *entry;
	int total_blocks;

	total_blocks = 0;

	if((dir = opendir(path)) == NULL)
	{
		ft_printf("ls: cannot open directory '%s': %s\n", path, strerror(errno));
		return -1;
	}

	while ((entry = readdir(dir)) != NULL)
	{
		if (!args->a && entry->d_name[0] == '.')
			continue;
		total_blocks += add_dir_files(files, args, ft_strjoin(path, "/"), ft_strdup(entry->d_name));
	}
	closedir(dir);
	return total_blocks;
}

void	display_files(t_list_files *list, bool l, char	*parent_dir)
{
	int	current_year;
	char	*link;
	char	*real_path;

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
				ft_printf("  ");
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

			ft_printf(" %s", list->file->path);
			if (list->file->perm[0] == 'l')
			{
				if ((link = (char *)malloc(list->file->size + 1)) != NULL)
				{
					real_path = ft_strjoin(parent_dir, list->file->path);		
					if (readlink(real_path, link, list->file->size + 1) != -1)
						ft_printf(" -> %s", link);

					free(link);
					free(real_path);
				}
			}
			ft_printf("\n");	
		}
		list = list->next;
	}
	free(parent_dir);
}

void	ft_ls(t_args *args)
{
	long int	total_blocks;
	t_list_files	*curr;
	t_list_files	*dir_files = NULL;
	bool		display_name = false;
	
	sorting_file(args, &args->list_not_dir);
	display_files(args->list_not_dir, (args->l) ? true : false, ft_strdup("./"));		

	if (!args->list_dir)
		return ;

	if (args->list_not_dir)
		write(1, "\n", 1);

	if (args->list_not_dir || ft_lstsize((t_list *)args->list_dir) > 1 || args->invalid_path)
		display_name = true;
	curr = args->list_dir;
	while (curr)
	{
		if (display_name)
			ft_printf("%s:\n", curr->file->path);
		total_blocks = get_dir_files(args, &dir_files,  curr->file->path);
		if (args->l && total_blocks != -1)
			ft_printf("total %d\n", total_blocks);
		sorting_file(args, &dir_files);
		display_files(dir_files, (args->l) ? true : false, ft_strjoin(curr->file->path, "/"));		

		curr = curr->next;
		if (curr)
			ft_printf("\n");
	}
	ft_lstclear((t_list **)&dir_files, del_file_list);
}
