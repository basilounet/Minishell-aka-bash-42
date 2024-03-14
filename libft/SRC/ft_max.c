/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 23:00:47 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/14 17:31:26 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

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
