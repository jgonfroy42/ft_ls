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

char	get_xattr(char *path)
{
	/*
 	* MAN: 
 	* GNU ls uses a ‘.’ character to indicate a file with a security context, but no other alternate access method.
 	* A file with any other combination of alternate access methods is marked with a ‘+’ character.
 	*
 	* listxattr:
 	* If security context: there will be a element name security.*** in the list (ex: security.selinux)
 	* If other alternative access, there will element not name security.
	*/ 

	size_t	size_buf, size_key;
	char	*buf, *to_free;
	char	*position;

	size_buf = listxattr(path, NULL, 0);
	if (size_buf > 0 && (buf = malloc(size_buf)))
	{
		size_buf = listxattr(path, buf, size_buf);

		to_free = buf;
		while (size_buf > 0)
		{
			position = ft_strnstr(buf, "security.", size_buf);
			if (!position)
			{
				free(to_free);
				return '+';
			}
			size_key = ft_strlen(buf) + 1;
			size_buf -= size_key;
			buf += size_key;
		}
		free(to_free);
		return '.';
	}
	return ' ';
}

bool	is_relative_path(char *path)
{
	if (path[0] == '.')
	{
		if (path[1] == '\0')
			return true;
		if (path[1] == '.' && path[2] == '\0')
			return true;
	}
	return false;
}

void	copy_args(t_args *src, t_args *dest)
{
	dest->recursion_call = true;

	dest->flags = src->flags;
	dest->list_not_dir = NULL;
	dest->list_dir = copy_list(src->recursion);

	dest->LEN_LINKS = 0;
	dest->LEN_OWNER = 0;
	dest->LEN_GROUP = 0;
	dest->LEN_SIZE = 0;
	dest->LEN_DEV_MAJ = 0;


	dest->recursion = NULL;
	dest->invalid_path = false;
}


long int	add_dir_files(t_list_files **list_files, t_args *args, char *dir_path, char *path)
{
	struct stat	buffer;
	t_file		*file;
	char		*real_path;

	real_path = ft_strjoin(dir_path, path);
	if ((args->flags & l_flag) == l_flag || (args->flags & t_flag) == t_flag)
	{
		if (lstat(real_path, &buffer) != 0)
		{
			print_error("ls: cannot acces '", path, strerror(errno));
			free(dir_path);
			free(real_path);
			return 0;
		}
		file = create_new_file(buffer, args->flags);
		if ((args->flags & l_flag) == l_flag)
			file->xattr = get_xattr(real_path);
		if ((args->flags & R_flag) == R_flag)
		{
			if (S_ISDIR(buffer.st_mode))
			{
				if (!is_relative_path(path))
				{
					t_file	*dir = init_file();
					dir->path = ft_strdup(real_path);
					ft_lstadd_back((t_list **)&args->recursion, ft_lstnew(dir));	
				}	
			}
		}
			
	}
	else
	{
		file = init_file();
		if ((args->flags & R_flag) == R_flag)
		{
			if (lstat(real_path, &buffer) != 0)
				print_error("ls: cannot acces '", path, strerror(errno));
			if (S_ISDIR(buffer.st_mode))
			{
				if (!is_relative_path(path))
				{
					t_file	*dir = init_file();
					dir->path = ft_strdup(real_path);
					ft_lstadd_back((t_list **)&args->recursion, ft_lstnew(dir));	
				}
			}
		}
	}

	file->path = path;
	ft_lstadd_back((t_list **)list_files, ft_lstnew(file));
	
	free(dir_path);
	free(real_path);

	if ((args->flags & l_flag) == l_flag)
	{
		char	*nb_links = ft_itoa(file->nb_links);

		if (ft_strlen(nb_links) > args->LEN_LINKS)
 			args->LEN_LINKS = ft_strlen(nb_links);
		free(nb_links);

		if (ft_strlen(file->owner) > args->LEN_OWNER)
 			args->LEN_OWNER = ft_strlen(file->owner);
		if (ft_strlen(file->group) > args->LEN_GROUP)
 			args->LEN_GROUP = ft_strlen(file->group);

		if (file->perm[0] == 'b' || file->perm[0] == 'c')
		{
			char	*nb_dev_major = ft_itoa(file->dev_major);
			char	*nb_dev_minor = ft_itoa(file->dev_minor);

			if (ft_strlen(nb_dev_major) > args->LEN_DEV_MAJ)
				args->LEN_DEV_MAJ = ft_strlen(nb_dev_major);
			if (ft_strlen(nb_dev_minor) > args->LEN_SIZE)
 				args->LEN_SIZE = ft_strlen(nb_dev_minor);
	
			free(nb_dev_major);
			free(nb_dev_minor);
		}
		else
		{
			char	*size = ft_itoa(file->size);
			if (ft_strlen(size) > args->LEN_SIZE)
 				args->LEN_SIZE = ft_strlen(size);
			free(size);
		}

		return buffer.st_blocks / 2;
	}
	return 0;
}

int	get_dir_files(t_args *args, t_list_files **files, char *path)
{
	DIR *dir;
	struct dirent *entry;
	int total_blocks;

	total_blocks = 0;
	args->LEN_LINKS = 0;
	args->LEN_OWNER = 0;
	args->LEN_GROUP = 0;
	args->LEN_SIZE = 0;
	args->LEN_DEV_MAJ = 0;

	if((dir = opendir(path)) == NULL)
	{
		print_error("ls: cannot open directory '", path, strerror(errno));
		return -1;
	}

	while ((entry = readdir(dir)) != NULL)
	{
	      	if ((args->flags & a_flag) != a_flag && entry->d_name[0] == '.')
			continue;
		if ((args->flags & A_flag) == A_flag && is_relative_path(entry->d_name))
			continue;
		total_blocks += add_dir_files(files, args, ft_strjoin(path, "/"), ft_strdup(entry->d_name));

	}
	closedir(dir);
	return total_blocks;
}

void	display_files(t_list_files *list, t_args *args, char *parent_dir, size_t len_col[5])
{
	char	link[1024];
	char	*real_path;

	while(list)
	{	
		if ((args->flags & l_flag) != l_flag)
			
		{
			ft_printf("%s", list->file->path);
			if (list->next && ((args->flags & one_flag) != one_flag))
				ft_printf("  ");
			else
				ft_printf("\n");
		}
		else
		{
			ft_printf("%s%c %*d %-*s %-*s ", list->file->perm, list->file->xattr, LEN_LINKS, list->file->nb_links, LEN_OWNER, list->file->owner, LEN_GROUP, list->file->group);
			/*
 			* LEN_COL need to include size of '$LEN_DEV_MAJOR, $LEN_DEV_MINOR' if there is c or b files
 			* in this case, LEN_DEV_MAJ != 0
 			*/
  
			if (list->file->perm[0] == 'c' || list->file->perm[0] == 'b')
				ft_printf("%*u, %*u ", LEN_DEV_MAJ, list->file->dev_major, LEN_SIZE,  list->file->dev_minor);
			else
				ft_printf("%*-u ", LEN_DEV_MAJ > 0 ? LEN_SIZE + LEN_DEV_MAJ + 2: LEN_SIZE, list->file->size);

			ft_printf("%s %2d ", list->file->date.month, list->file->date.day);

			if (list->file->date.old)
				ft_printf(" %d", list->file->date.year);
			else
				ft_printf("%02d:%02d", list->file->date.hour, list->file->date.minutes);

			ft_printf(" %s", list->file->path);
			if (list->file->perm[0] == 'l')
			{
				int size_ret;
				real_path = ft_strjoin(parent_dir, list->file->path);		
				if ((size_ret = readlink(real_path, link, 1023)) != -1)
				{
					link[size_ret] = '\0';	
					ft_printf(" -> %s", link);
				}
				free(real_path);
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

/*
 * tri et affichage des arguments autres que les dir
 */

	sorting_file(args, &args->list_not_dir);
	display_files(args->list_not_dir, args, ft_strdup("./"), args->len_col);

	if (!args->list_dir)
		return ;

	if (args->list_not_dir || args->recursion_call)
		write(1, "\n", 1);

/*
 * tri, récupération du contenu et affichage des args dir
 */

	if (args->list_not_dir || ft_lstsize((t_list *)args->list_dir) > 1 || args->invalid_path || (args->flags & R_flag) == R_flag)
		display_name = true;
	sorting_file(args, &args->list_dir);
	curr = args->list_dir;
	while (curr)
	{
		if (display_name)
			ft_printf("%s:\n", curr->file->path);

		total_blocks = get_dir_files(args, &dir_files,  curr->file->path);
		
		if ((args->flags & l_flag) == l_flag && total_blocks != -1)
			ft_printf("total %d\n", total_blocks);
		sorting_file(args, &dir_files);
		display_files(dir_files, args, ft_strjoin(curr->file->path, "/"), args->len_col);
		if ((args->flags & R_flag) == R_flag)
		{
			t_args	*recursion_args = (t_args*)malloc(sizeof(t_args));
			copy_args(args, recursion_args);
			ft_ls(recursion_args);
			ft_lstclear((t_list **)&recursion_args->list_dir, del_file_list);
			free(recursion_args);
		}	
		curr = curr->next;
		if (curr)
			ft_printf("\n");
		ft_lstclear((t_list **)&dir_files, del_file_list);
		ft_lstclear((t_list **)&args->recursion, del_file_list);
		args->recursion = NULL;
	}
	ft_lstclear((t_list **)&args->recursion, del_file_list);
}
