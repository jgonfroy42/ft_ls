#include "../include/ft_ls.h"
#include <ctype.h>  // <cctype> en C++

int	convert_month(char *month)
{
	if (ft_strncmp(month, "Jan", 3))
		return 1;
	if (ft_strncmp(month, "Feb", 3))
		return 2;
	if (ft_strncmp(month, "Mar", 3))
		return 3;
	if (ft_strncmp(month, "Apr", 3))
		return 4;
	if (ft_strncmp(month, "May", 3))
		return 5;
	if (ft_strncmp(month, "Jun", 3))
		return 6;
	if (ft_strncmp(month, "Jul", 3))
		return 7;
	if (ft_strncmp(month, "Aug", 3))
		return 8;
	if (ft_strncmp(month, "Sep", 3))
		return 9;
	if (ft_strncmp(month, "Oct", 3))
		return 10;
	if (ft_strncmp(month, "Nov", 3))
		return 11;
	if (ft_strncmp(month, "Dec", 3))
		return 12;

	return -1;
}

bool	is_date_sorted(t_time t1, t_time t2)
{
	int	month_1;
	int	month_2;

	if (t1.year > t2.year)
		return true;
	if (t1.year < t2.year)
		return false;

	month_1 = convert_month(t1.month);
	month_2 = convert_month(t2.month);

	if (month_1 > month_2)
		return true;
	if (month_1 < month_2)
		return false;
	if (t1.day > t2.day)
		return true;
	if (t1.day < t2.day)
		return false;
	if (t1.hour > t2.hour)
		return true;
	if (t1.hour < t2.hour)
		return false;
	if (t1.minutes > t2.minutes)
		return true;
	if (t1.minutes < t2.minutes)
		return false;
	return true;
}


bool	is_ascii_sorted(char *s1, char *s2)
{
	size_t	i = 0;

	while (i < ft_strlen(s1) && i < ft_strlen(s2))
	{
		if (s1[i] < s2[i])
			return true;
		if (s2[i] < s1[i])
			return false;
		i++;
	}

	if (ft_strlen(s1) < ft_strlen(s2))
		return true;
	if (ft_strlen(s1) > ft_strlen(s2))
		return false;
	
	return true;
}

t_list_files	*sort_files(t_args *args, t_list_files *a,t_list_files *b)
{
	t_list_files *ret = NULL;

	if (a == NULL)
		return b;
	if (b == NULL)
		return a;

	if (args->t)
	{
		if (is_date_sorted(a->file->date, b->file->date))
		{
			if (!args->r)
			{
				ret = a;
				ret->next = sort_files(args, a->next, b);
			}	
			else
			{
				ret = b;
				ret->next = sort_files(args, a, b->next);
			}
		}
		else
		{
			if (args->r)
			{
				ret = a;
				ret->next = sort_files(args, a->next, b);
			}	
			else
			{
				ret = b;
				ret->next = sort_files(args, a, b->next);
			}
		}
	}

	else
	{
		if (is_ascii_sorted(a->file->path, b->file->path))
		{
			if (!args->r)
			{
				ret = a;
				ret->next = sort_files(args, a->next, b);
			}	
			else
			{
				ret = b;
				ret->next = sort_files(args, a, b->next);
			}
		}
		else
		{
			if (args->r)
			{
				ret = a;
				ret->next = sort_files(args, a->next, b);
			}	
			else
			{
				ret = b;
				ret->next = sort_files(args, a, b->next);
			}
		}
	}

	return (ret);
}

void	split_list(t_list_files *source, t_list_files **sub_a, t_list_files **sub_b)
{
	t_list_files	*slow = source;
	t_list_files	*fast = source->next;

	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}

	*sub_a = source;
	*sub_b = slow->next;
	slow->next = NULL;
}

void	sorting_file(t_args *args, t_list_files **files)
{
	/*
 	* algo général qui trie selon n'importe quel critère. 
 	* au moment de trier choix fait grâce à args ?
 	*/

	t_list_files	*head = *files;
	t_list_files	*sublist_a;
	t_list_files	*sublist_b;

	if (!head || !head->next)
		return ;
	split_list(head, &sublist_a, &sublist_b);
	sorting_file(args, &sublist_a);
	sorting_file(args, &sublist_b);

	*files = sort_files(args, sublist_a, sublist_b);

}
