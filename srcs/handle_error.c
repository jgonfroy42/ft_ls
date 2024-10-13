#include "../include/ft_ls.h"

void	print_error(char *problem, char *path, char *strerr)
{
	ft_putstr_fd(problem, 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd("': ", 2);
	ft_putstr_fd(strerr, 2);
	ft_putstr_fd("\n", 2);
}
