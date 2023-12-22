#include "../include/ft_ls.h"

void	is_option_valid(t_args *parsed_args, char *option)
{
	for (int i = 0; option[i] != 0; i++)
	{
		if (!ft_strchr(parsed_args->valid, option[i]))
		{
			ft_printf("ls : invalid option -- %c", option[i]);
			exit(1);
		}

		switch (option[i])
		{
			case 'l': parsed_args->l = true; break;
			case 'R': parsed_args->R = true; break;
			case 'a': parsed_args->a = true; break;
			case 'r': parsed_args->r = true; break;
			case 't': parsed_args->t = true; break;
		}
	}
}

t_file	*create_new_file(struct stat buffer)
{
	t_file	*file = (t_file*)malloc(sizeof(t_file));

/*
 * set type of file
 */
	switch (buffer.st_mode & S_IFMT)
	{
                        case S_IFBLK:  file->type = 'b';                 break;
                        case S_IFCHR:  file->type = 'c';                 break;
                        case S_IFDIR:  file->type = 'd';                 break;
                        case S_IFIFO:  file->type = 'p';                 break;
                        case S_IFLNK:  file->type = 'l';                 break;
                        case S_IFREG:  file->type = '-';                 break;
                        case S_IFSOCK: file->type = 's';                 break;
                        default:       file->type = 'n';          break;
                }
	return file;
}

int	add_file(t_args *parsed_args, char *path)
{
	struct	stat buffer;
	t_file	*file_info;	

	if (stat(path, &buffer) != 0)
		return 0;
	
	file_info = create_new_file(buffer);
	file_info->path = path;
	if (file_info->type == 'd')
		ft_lstadd_back((t_list **)&parsed_args->list_dir, ft_lstnew(file_info));
	else
		ft_lstadd_back((t_list **)&parsed_args->list_not_dir, ft_lstnew(file_info));
		
	return 1;
}


int	parse_args(t_args *parsed_args, char **args)
{
/*
 * 1. on verif les args :
 * - soit pas d'args
 * - arg qui commence par "-" => on verifie que les options sont valides
 *   -> si faux message d'erreur et on arrête tout
 * - autres args, on verifie que le chemin est valide
 *   -> message d'erreur pour les chemins faut puis on exécute la commande pour les autres
 *
 *  2. que fait-on des args ?
 *  struct avec bool les options possibles à false par defaut
 *  liste chainée de path pour les args.
 *  ATTENTION : utilisation diff entre dir et not dir => deux listes diff nécessaires
 *
 *  utilisation de stat pour vérifier la validité du chemin je stock les informations pour ne pas faire nouveau stat plus tard. Utile pour -t et -l.
*/

	while (*(++args) != NULL)
	{
		if ((*args)[0] == '-' && (*args)[1] != 0)
			is_option_valid(parsed_args, &((*args)[1]));
		else
			if (!add_file(parsed_args, *args))
				ft_printf("ls: cannot access '%s': No such file or directory\n", *args);
	}
	return 0;
}
