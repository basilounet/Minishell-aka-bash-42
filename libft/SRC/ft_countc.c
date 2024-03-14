/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:54:01 by bvasseur          #+#    #+#             */
/*   Updated: 2023/11/27 21:57:13 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_countc(char *str, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
		if (str[i++] == c)
			count++;
	return (count);
}
