#include "../include/ft_ls.h"

t_args	is_option_valid(t_args parsed_args, char *option)
{
	for (int i = 0; option[i] != 0; i++)
	{
		if (!ft_strchr(parsed_args.valid, option[i]))
		{
			ft_printf("ls : invalid option -- %c", option[i]);
			exit(1);
		}

		switch (option[i])
		{
			case 'l': parsed_args.l = true; break;
			case 'R': parsed_args.R = true; break;
			case 'a': parsed_args.a = true; break;
			case 'r': parsed_args.r = true; break;
			case 't': parsed_args.t = true; break;
		}
	}

	return parsed_args;
}

bool	is_path_valid(char *path)
{
    struct stat buffer;
    return stat(path, &buffer) == 0 ? true : false;
}


t_args	parse_args(char **args)
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
 *  liste chainée de path, si vide => on prend . par défaut
 *  struct avec bool des args possibles à false par defaut

*/

	t_args parsed_args = {
		.valid = "lRart",
		
		.l = false,
		.R = false,
		.a = false,
		.r = false,
		.t = false,
	};

	parsed_args.list_paths = (t_paths*)ft_lstnew("");	
	
	t_paths	*current = parsed_args.list_paths;
	t_paths	*to_iter = current->next;

	while (*(++args) != NULL)
	{
		if ((*args)[0] == '-' && (*args)[1] != 0)
		{
			parsed_args = is_option_valid(parsed_args, &((*args)[1]));
		}
		else
		{
			if (is_path_valid(*args))
			{
				to_iter = (t_paths *)ft_lstnew(*args);
				current->next = to_iter;
				to_iter = to_iter->next;
				current = current->next;				
			}
			else
				ft_printf("ls: cannot access '%s': No such file or directory\n", *args);
		}
	}
	if (parsed_args.list_paths == NULL)
		ft_printf("null\n");
	return parsed_args;
}
