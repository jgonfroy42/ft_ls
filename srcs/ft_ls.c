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
			ft_printf("%s. %d %s %s %d %s %s\n", list->file->perm, list->file->nb_links, list->file->owner, list->file->group, list->file->size, ft_substr(list->file->date, 4, 12), list->file->path);
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
		//ft_lstadd_back((t_list **)&args->list_dir, ft_lstnew(create_file(".")));
		add_file(args, ".");
	//test
	sorting_file(args, args->list_not_dir);
	display_not_dir(args->list_not_dir, (args->l) ? true : false);		
}
