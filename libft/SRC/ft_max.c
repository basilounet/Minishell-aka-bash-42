/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 23:00:47 by bvasseur          #+#    #+#             */
/*   Updated: 2024/01/30 18:29:23 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

long	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
