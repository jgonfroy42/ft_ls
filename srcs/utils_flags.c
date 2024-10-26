#include "../include/ft_ls.h"

bool has_flag(int16_t flags, int to_check)
{
	return ((flags & to_check) == to_check);
}

bool has_any_flag(int16_t flags, int to_check)
{
	return ((flags & to_check) != 0);
}
