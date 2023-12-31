#include "../include/ft_ls.h"

/*
 * add_file : doit pouvoir être utilisé au moment du parsing et par ft_ls.
 * Pb : depuis ft_ls : besoin d'avoir les arguments pour pas récupérer des infos inutiles.
 * Mais : au moment du parsing, on ne connait pas encore tous les arguments donc on ouvre tout par défaut
 * comment faire intelligement la diff ? 
*/


t_time	convert_time(char *stime)
{
	t_time time;
	char	*sub_str;

	sub_str = ft_substr(stime, 20, 4);
	time.year = ft_atoi(sub_str);
	free(sub_str);

	time.month = ft_substr(stime, 4, 3);

	sub_str = ft_substr(stime, 8, 2);
	time.day = ft_atoi(sub_str);
	free(sub_str);

	sub_str = ft_substr(stime, 11, 2);
	time.hour = ft_atoi(sub_str);
	free(sub_str);

	sub_str = ft_substr(stime, 14, 2); 	
	time.minutes = ft_atoi(sub_str);
	free(sub_str);
	
	return time;
}

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

t_file	*create_new_file(struct stat buffer, bool l, bool t)
{
	/*
 	* total of dir is sum of buffer.st_blocks;
 	*/ 

	struct passwd  *pwd;
	struct group   *grp;
	t_file	*file;

	file = (t_file*)malloc(sizeof(t_file));
	file->date.month = NULL;

	if (!l && !t)
		return file;
	
	file->date = convert_time(ctime(&buffer.st_mtime));
	if (!l)
		return file;
	
	switch (buffer.st_mode & S_IFMT)
	{
		case S_IFBLK:  file->perm[0] = 'b'; break;
		case S_IFCHR:  file->perm[0] = 'c'; break;
		case S_IFDIR:  file->perm[0] = 'd'; break;
		case S_IFIFO:  file->perm[0] = 'p'; break;
		case S_IFLNK:  file->perm[0] = 'l'; break;
		case S_IFREG:  file->perm[0] = '-'; break;
		case S_IFSOCK: file->perm[0] = 's'; break;
		default:       file->perm[0] = '-'; break;
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
	file->perm[10] = 0;

	file->nb_links = (buffer.st_nlink);
	file->size = (buffer.st_size);

	file->owner = ((pwd = getpwuid(buffer.st_uid))) ? pwd->pw_name : ft_itoa(buffer.st_uid);
 	file->group = ((grp = getgrgid(buffer.st_gid))) ? grp->gr_name : ft_itoa(buffer.st_gid); 

	return file;
}

void	add_file(t_args *parsed_args, char *path)
{
	struct	stat buffer;
	t_file	*file_info;	

	if (lstat(path, &buffer) != 0)
	{
		ft_printf("ls: cannot access '%s': %s\n", path, strerror(errno));
		parsed_args->invalid_path = true;
		return ;
	}
	
	file_info = create_new_file(buffer, parsed_args->l, parsed_args->t);
	file_info->path = ft_strdup(path);

	if (S_ISDIR(buffer.st_mode))
		ft_lstadd_back((t_list **)&parsed_args->list_dir, ft_lstnew(file_info));
	else
		ft_lstadd_back((t_list **)&parsed_args->list_not_dir, ft_lstnew(file_info));
}


int	parse_args(t_args *parsed_args, char **args)
{
/*
 *
 * 1. on verif les args :
 * - soit pas d'args
 * - arg qui commence par "-" => on verifie que les options sont valides
 *   -> si faux message d'erreur et on arrête tout
 * - autres args, on fait une liste des chemins pour s'en occuper plus tard 
 *   Pourquoi : pas de msg d'erreur pour un chemin invalide si il y a une option invalide même après
 * - une fois finie, on vérífie la liste des chemins
 *   -> message d'erreur pour les chemins faux puis on exécute la commande pour les autres
 *
 *  2. que fait-on des args ?
 *  struct avec bool les options possibles à false par defaut
 *  liste chainée de files pour les args.
 *  ATTENTION : utilisation diff entre dir et not dir => deux listes diff nécessaires
 *
 *  utilisation de stat pour vérifier la validité du chemin je stock les informations pour ne pas faire nouveau stat plus tard. Utile pour -t et -l.
*/
	t_list_raw_args	*list_paths;
	t_list_raw_args	*curr;

	list_paths = NULL;

	while (*(++args) != NULL)
	{
		if ((*args)[0] == '-' && (*args)[1] != 0)
			is_option_valid(parsed_args, &((*args)[1]));
		else
			ft_lstadd_back((t_list **)&list_paths, ft_lstnew(*args));
	}

	curr = list_paths;
	while (curr)
	{
		add_file(parsed_args, curr->path);
		curr = curr->next;
	}
	ft_lstclear((t_list **)&list_paths, del_path_list);
	
 	// if no args, we display current dir
	if (ft_lstsize((t_list *)parsed_args->list_dir) == 0 && ft_lstsize((t_list *)parsed_args->list_not_dir) == 0 && !parsed_args->invalid_path)
		add_file(parsed_args, ".");

	return 0;
}
