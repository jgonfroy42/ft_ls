/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgonfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 16:01:37 by jgonfroy          #+#    #+#             */
/*   Updated: 2019/11/13 17:49:45 by jgonfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	unsigned int	i;
	char			*str;
	size_t			len;

	i = 0;
	len = ft_strlen(s1);
	if (!(str = ft_calloc(len + 1, sizeof(char))))
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	return (str);
}
