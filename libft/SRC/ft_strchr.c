/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:22:00 by marvin            #+#    #+#             */
/*   Updated: 2024/03/15 18:11:47 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strchr(const char *str, int to_find)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)to_find)
			return ((char *)&(str[i]));
		i++;
	}
	if (!to_find)
		return ((char *)str + i);
	return (NULL);
}

char	*ft_strchrn(const char *str, int to_find, int n)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (n < 1)
		return (NULL);
	while (str[i])
	{
		if (str[i] == (char)to_find)
			if (++count >= n)
				return ((char *)&(str[i]));
		i++;
	}
	if (!to_find)
		return ((char *)str + i);
	return (NULL);
}
