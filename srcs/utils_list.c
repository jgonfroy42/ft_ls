#include "../include/ft_ls.h"

void	del_file_list(void *elem)
{
	free(elem);
}
