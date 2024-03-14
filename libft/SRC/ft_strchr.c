/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:22:00 by marvin            #+#    #+#             */
/*   Updated: 2024/03/14 17:32:40 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strchr(const char *str, int to_find)
{
	unsigned int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)to_find)
			return ((char *) &(str[i]));
		i++;
	}
	if (!to_find)
		return ((char *) str + i);
	return (NULL);
}
