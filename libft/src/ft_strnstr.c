/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:10:25 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/15 18:02:39 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (ft_strlen(to_find) == 0)
		return ((char *)str);
	while (str[i] && i < len)
	{
		j = 0;
		while (str[i + j] == to_find[j] && str[i + j] && i + j < len)
			j++;
		if (j == ft_strlen(to_find))
			return ((char *)&(str[i]));
		i++;
	}
	return ((char *)0);
}

char	*ft_map_strstr(char **str, char *to_find)
{
	int		i;

	i = -1;
	if (!str)
		return (NULL);
	while (str[++i])
		if (ft_strnstr(str[i], to_find, ft_strlen(str[i])))
			return (ft_strnstr(str[i], to_find, ft_strlen(str[i])));
	return (NULL);
}
