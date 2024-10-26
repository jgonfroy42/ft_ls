#include "../include/ft_ls.h"

/*
 * add_file : doit pouvoir être utilisé au moment du parsing et par ft_ls.
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
		if (!ft_strchr(VALID_FLAGS, option[i]))
		{
			ft_printf("ls : invalid option -- %c", option[i]);
			exit(1);
		}
	/*
	 * in case of -A and -a, the last one count
	 */
		switch (option[i])
		{
			case 'l': parsed_args->flags |= (l_flag); break;
			case 'R': parsed_args->flags |= (R_flag); break;
			case 'a': parsed_args->flags |= (a_flag ); parsed_args->flags &= ~(A_flag);  break;
			case 'r': parsed_args->flags |= (r_flag); break;
			case 't': parsed_args->flags |= (t_flag); break;
			case 'd': parsed_args->flags |= (d_flag); break;
			case 'A': parsed_args->flags |= (A_flag | a_flag) ; break;
			case '1': parsed_args->flags |= (one_flag); break;
		}
	}
}

t_file	*init_file()
{
	t_file	*file;
	
	file = (t_file*)malloc(sizeof(t_file));
	if (file)
	{
		file->date.month = NULL;
		file->owner = NULL;
		file->group = NULL;
	}
	return file;
}

t_file	*create_new_file(struct stat buffer, int flags)
{
	/*
 	* total of dir is sum of buffer.st_blocks;
 	*/ 

	struct passwd  *pwd;
	struct group   *grp;
	t_file	*file;

	file = init_file();

	if (((flags & (l_flag | t_flag)) == 0) || !file)
		return file;
	
	file->date = convert_time(ctime(&buffer.st_mtime));

	/*
 	* display time if file less than 6 months old; else display year
 	* we check it now so we can get rid of st_mtime;
 	*/	
	time_t diff = time(NULL) - buffer.st_mtime;
	file->date.old = true;
	if (((diff / 6) / (365.25 / 12)) / 24 < 3600)
		file->date.old = false;

	if ((flags & l_flag) != l_flag)
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
	file->perm[4] = (buffer.st_mode & S_IRGRP) ? 'r' : '-';
	file->perm[5] = (buffer.st_mode & S_IWGRP) ? 'w' : '-';
	file->perm[7] = (buffer.st_mode & S_IROTH) ? 'r' : '-';
	file->perm[8] = (buffer.st_mode & S_IWOTH) ? 'w' : '-';


	//droits speciaux	
	if (buffer.st_mode & S_ISUID)
		file->perm[3] = (buffer.st_mode & S_IXUSR) ? 's' : 'S';
	else
		file->perm[3] = (buffer.st_mode & S_IXUSR) ? 'x' : '-';
	if (buffer.st_mode & S_ISGID)
		file->perm[6] = (buffer.st_mode & S_IXGRP) ? 's' : 'S';
	else
		file->perm[6] = (buffer.st_mode & S_IXGRP) ? 'x' : '-';

	if (buffer.st_mode & S_ISVTX)
		file->perm[9] = (buffer.st_mode & S_IXOTH) ? 't' : 'T';
	else
		file->perm[9] = (buffer.st_mode & S_IXOTH) ? 'x' : '-';
	

	file->perm[10] = 0;
	
	file->nb_links = (buffer.st_nlink);

	file->owner = ((pwd = getpwuid(buffer.st_uid))) ? ft_strdup(pwd->pw_name) : ft_strdup(ft_itoa(buffer.st_uid));
 	file->group = ((grp = getgrgid(buffer.st_gid))) ? ft_strdup(grp->gr_name) : ft_strdup(ft_itoa(buffer.st_gid)); 

	if (file->perm[0] == 'b' || file->perm[0] == 'c')
	{
		file->dev_major = major(buffer.st_rdev);
		file->dev_minor = minor(buffer.st_rdev);
	}
	else
		file->size = (buffer.st_size);

	return file;
}

void	add_file(t_args *parsed_args, char *path)
{
	struct	stat buffer;
	struct	stat buffer_symlink;
	t_file	*file_info;	

	if (lstat(path, &buffer) != 0)
	{
		print_error("ls: cannot access '", path, strerror(errno));
		parsed_args->invalid_path = true;
		return ;
	}
	
	file_info = create_new_file(buffer, parsed_args->flags);
	file_info->path = ft_strdup(path);
	if ((parsed_args->flags & d_flag) == d_flag)
	{
		ft_lstadd_back((t_list **)&parsed_args->list_not_dir, ft_lstnew(file_info));
		return ;
	} 

	if (S_ISDIR(buffer.st_mode))
		ft_lstadd_back((t_list **)&parsed_args->list_dir, ft_lstnew(file_info));
	/*
 	* symlink on a dir:
 	* IF -l THEN
 	* 	symlink act like a file
 	* ELSE
 	* 	act like a dir
 	*/
  
	else if ((parsed_args->flags & l_flag) != l_flag && !stat(path, &buffer_symlink) && S_ISDIR(buffer_symlink.st_mode))
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
 *   Pourquoi ? pas de msg d'erreur pour un chemin invalide si il y a une option invalide même après
 * - une fois fini, on vérífie la liste des chemins
 *   -> message d'erreur pour les chemins faux puis on exécute la commande pour les autres
 *
 *  2. que fait-on des args ?
 *  struct avec bool les options possibles à false par defaut
 *  liste chainée de files pour les args.
 *  ATTENTION : utilisation diff entre dir et not dir => deux listes diff nécessaires
 *
 *  utilisation de stat pour vérifier la validité du chemin et stocker les informations nécessaires (dépend de -t et -l).
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
	
 	/*
 	*  if no paths (valid or invalid), arg is current dir
	*/
	if (!list_paths)
		add_file(parsed_args, ".");

	ft_lstclear((t_list **)&list_paths, del_elem);
	return 0;
}
