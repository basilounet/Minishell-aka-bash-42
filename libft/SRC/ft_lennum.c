/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lennum.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:20:53 by bvasseur          #+#    #+#             */
/*   Updated: 2024/01/15 15:11:18 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lennum(long nb)
{
	int	count;

	count = nb < 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb /= 10;
		count++;
	}
	return (count);
}
