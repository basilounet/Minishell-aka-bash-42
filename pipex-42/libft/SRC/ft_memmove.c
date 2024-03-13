/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:13:35 by bvasseur          #+#    #+#             */
/*   Updated: 2023/11/02 15:07:55 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*area_dest;
	char	*area_src;

	i = 0;
	area_dest = dest;
	area_src = (void *)src;
	if (src < dest)
	{
		while (n > 0)
		{
			area_dest[n - 1] = area_src[n - 1];
			n--;
		}
		return (dest);
	}
	while (i < n)
	{
		area_dest[i] = area_src[i];
		i++;
	}
	return (dest);
}
