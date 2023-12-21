#include "../include/ft_ls.h"

void	display_list(void *path)
{
	ft_printf("%s\n", path);
}

void	test_parsing(t_args args)
{
/*
 * Affiche les options détectées dans le parsing et les chemins considérés comme valides
 */
	void	(*pfunc)(void *) = &display_list;

	ft_printf("---TEST DU PARSING---\n\n");
	ft_printf("l : %i\na : %i\nR : %i\nr : %i\nt : %i\n", args.l, args.a, args.R, args.r, args.t);
	ft_lstiter((t_list *)args.list_paths, pfunc);
	if (args.list_paths == NULL)
		ft_printf("null");
}


int main(int ac, char **av)
{
	(void)ac;
	t_args	args;

	args = parse_args(av);

	test_parsing(args);
}
