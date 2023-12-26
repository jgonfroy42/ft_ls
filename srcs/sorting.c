#include "../include/ft_ls.h"
#include <ctype.h>  // <cctype> en C++

bool	is_alpha_sorted(char *s1, char *s2)
{
	size_t	i;
	char	c1;
	char	c2;

	i = 0;

	while (i < ft_strlen(s1) && i < ft_strlen(s2))
	{
		
		c1 = ft_toupper(s1[i]);
		c2 = ft_toupper(s2[i]);
		if (c1 < c2)
			return true;
		if (c2 < c1)
			return false;
		i++;
	}

	if (ft_strlen(s1) < ft_strlen(s2))
		return true;
	if (ft_strlen(s1) > ft_strlen(s2))
		return false;

	i = 0;	
	while (i < ft_strlen(s1))
	{
		if (ft_isupper(s1[i]) != ft_isupper(s2[i]))
		{
			if (ft_islower(s1[i]))
				return true;
			return false;
		}
		i++;
	}
	
	return true;
}

t_list_files	*sort_files(t_args *args, t_list_files *a,t_list_files *b)
{
	t_list_files *ret = NULL;

	if (a == NULL)
		return b;
	if (b == NULL)
		return a;
	if (!args->t)
	{
		if (is_alpha_sorted(a->file->path, b->file->path))
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

void	merge_sort(t_args *args, t_list_files **list)
{
	t_list_files	*head = *list;
	t_list_files	*sublist_a;
	t_list_files	*sublist_b;

	if (!head || !head->next)
		return ;
	split_list(head, &sublist_a, &sublist_b);
	merge_sort(args, &sublist_a);
	merge_sort(args, &sublist_b);

	*list = sort_files(args, sublist_a, sublist_b);
}

void	sorting_file(t_args *args, t_list_files **files)
{
/*
 * algo général qui trie selon n'importe quel critère. 
 * au moment de trier choix fait grâce à args ?
 */
	merge_sort(args, files);

}
