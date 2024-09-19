#include "../include/ft_ls.h"

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
	args->recursion = NULL;

	args->len_col[0] = 0;
	args->len_col[1] = 0;
	args->len_col[2] = 0;
	args->len_col[3] = 0;

	args->invalid_path = false;
	args->recursion_call = false;
}

int main(int ac, char **av)
{
	(void)ac;
	t_args *args = (t_args*)malloc(sizeof(t_args));

	init_struct(args);
	parse_args(args, av);
	ft_ls(args);

/*
 * test
 */
	//tests(args);

/*
 * clean
 */
	ft_lstclear((t_list **)&args->list_dir, del_file_list);
	ft_lstclear((t_list **)&args->list_not_dir, del_file_list);
	ft_lstsize((t_list *)args->list_not_dir);
	free(args);
}
