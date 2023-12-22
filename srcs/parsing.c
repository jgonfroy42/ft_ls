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
 * set permissions
 * fisrt char = type of file
 */
	switch (buffer.st_mode & S_IFMT)
	{
		case S_IFBLK:  file->perm[0] = 'b'; break;
		case S_IFCHR:  file->perm[0] = 'c'; break;
		case S_IFDIR:  file->perm[0] = 'd'; break;
		case S_IFIFO:  file->perm[0] = 'p'; break;
		case S_IFLNK:  file->perm[0] = 'l'; break;
		case S_IFREG:  file->perm[0] = '-'; break;
		case S_IFSOCK: file->perm[0] = 's'; break;
		default:       file->perm[0] = 'n'; break;
	}

	file->perm[1] = (buffer.st_mode & S_IRUSR) ? 'r' : '-';
	file->perm[2] = (buffer.st_mode & S_IWUSR) ? 'w' : '-';
	file->perm[3] = (buffer.st_mode & S_IXUSR) ? 'x' : '-';
	file->perm[4] = (buffer.st_mode & S_IRGRP) ? 'r' : '-';
	file->perm[5] = (buffer.st_mode & S_IWGRP) ? 'w' : '-';
	file->perm[6] = (buffer.st_mode & S_IXGRP) ? 'x' : '-';
	file->perm[7] = (buffer.st_mode & S_IROTH) ? 'r' : '-';
	file->perm[8] = (buffer.st_mode & S_IWOTH) ? 'w' : '-';
	file->perm[9] = (buffer.st_mode & S_IXOTH) ? 'x' : '-';

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

	if (S_ISDIR(buffer.st_mode))
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
