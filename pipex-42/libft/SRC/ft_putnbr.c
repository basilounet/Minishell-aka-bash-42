/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:22:53 by marvin            #+#    #+#             */
/*   Updated: 2024/01/15 15:13:06 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	recurse(int n)
{
	int	unit;

	if (ft_abs(n) > 9)
		recurse(n / 10);
	unit = ft_abs(n % 10) + 48;
	write(1, &unit, 1);
}

int	ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
		write(1, "-", 1);
	recurse(n);
	return (ft_lennum(n));
}
