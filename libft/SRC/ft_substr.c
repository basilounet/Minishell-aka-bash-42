/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:39:15 by bvasseur          #+#    #+#             */
/*   Updated: 2023/11/03 18:32:43 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len(char const *str, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && str[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t n)
{
	char	*str;
	size_t	len_str;
	size_t	i;

	i = 0;
	len_str = ft_strlen(s);
	if (n <= 0 || start > len_str)
		return (ft_strdup("\0"));
	str = (char *)malloc(sizeof(char) * len(&s[start], n) + 1);
	if (str == NULL)
		return (NULL);
	while (i < n && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}
