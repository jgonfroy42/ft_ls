#include "../include/ft_ls.h"

void	display_list(void *file)
{
	ft_printf("elem :%s\n", ((t_file *)file)->path);
}

void	test_parsing(t_args *args)
{
/*
 * Affiche les options détectées dans le parsing et les chemins considérés comme valides
 */
	void	(*pfunc)(void *) = &display_list;

	ft_printf("---TEST DU PARSING---\n\n");
	ft_printf("l : %i\na : %i\nR : %i\nr : %i\nt : %i\n", args->l, args->a, args->R, args->r, args->t);

	ft_printf("\nDirectory\n");
	ft_lstiter((t_list *)args->list_dir, pfunc);

	ft_printf("\nNot directory\n");
	ft_lstiter((t_list *)args->list_not_dir, pfunc);
}

void	init_struct(t_args *args)
{
	args->valid = "lRart";
		
	args->l = false;
	args->R = false;
	args->a = false;
	args->r = false;
	args->t = false;
		
	args->list_dir = NULL;
	args->list_not_dir = NULL;
}

int main(int ac, char **av)
{
	(void)ac;
	void	(*pfunc)(void *) = &del_one_path_list;

	t_args *args = (t_args*)malloc(sizeof(t_args));

	init_struct(args);
	parse_args(args, av);
	ft_ls(args);

/*
 * test
 */
	test_parsing(args);

/*
 * clean
 */
	ft_lstclear((t_list **)&args->list_dir, pfunc);
	ft_lstclear((t_list **)&args->list_not_dir, pfunc);
	free(args);
}
