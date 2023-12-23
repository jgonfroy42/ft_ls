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

	args->length_col_owner = 0;
	args->length_col_group = 0;
	args->length_col_size = 0;
}

int main(int ac, char **av)
{
	(void)ac;
	void	(*pfunc)(void *) = &del_file_list;

	t_args *args = (t_args*)malloc(sizeof(t_args));

	init_struct(args);
	parse_args(args, av);
	ft_ls(args);

/*
 * test
 */
	tests(args);

/*
 * clean
 */
	ft_lstclear((t_list **)&args->list_dir, pfunc);
	ft_lstclear((t_list **)&args->list_not_dir, pfunc);
	free(args);
}
