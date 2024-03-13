/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbru.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:37:24 by bvasseur          #+#    #+#             */
/*   Updated: 2024/01/15 15:13:13 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	recurse(unsigned long n)
{
	int	unit;

	if (n > 9)
		recurse(n / 10);
	unit = n % 10 + 48;
	write(1, &unit, 1);
}

int	ft_putnbru(unsigned long n)
{
	if (n < 0)
		write(1, "-", 1);
	recurse(n);
	return (ft_lennum(n));
}
