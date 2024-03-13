/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:53:32 by bvasseur          #+#    #+#             */
/*   Updated: 2024/01/20 18:34:57 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	gen_bit_shift(unsigned int seed, unsigned int keys[4])
{
	int	k1;
	int	k2;
	int	k3;

	k1 = (seed >> 4) + 5555 ^ ((seed << 22) * 8);
	k2 = k1 * (k1 % 42) * k1 * (k1 % 13) * (k1 / 4) * (k1 + seed);
	k3 = (seed << 2 ^ 5) % 5 + 5 * (seed | 453871);
	keys[0] = (k1 * ft_lennum(seed)) | 45657;
	keys[1] = keys[0] ^ 0x4f56a % (ft_lennum(k1) << 12) * k3;
	keys[2] = (keys[0] | keys[1]) / ((465 >> 4 ^ 5));
	keys[3] = k1 * seed - ((k3 * ft_abs(k2) * k1) | seed);
}

int	ft_rrand(int init, unsigned int seed, unsigned int min, unsigned int max)
{
	static unsigned int	s_seed;
	unsigned int		keys[4];
	int					range;

	range = max - min + 1;
	if (init)
	{
		s_seed = seed;
		return (s_seed);
	}
	gen_bit_shift(s_seed, keys);
	s_seed = ((keys[3] ^ 4) & 0x4f3ba2) / ft_memcmp(keys, &keys[2],
			ft_lennum(keys[3]));
	s_seed += 3;
	s_seed <<= 3;
	s_seed *= keys[1] * (ft_lennum(keys[1])) * (keys[0] << ft_lennum(s_seed))
		+ 0xfac2d;
	s_seed |= ((keys[2] / 4) >> 3);
	return ((s_seed % range) + min);
}

void	ft_srand(unsigned int seed)
{
	if (seed == 0)
		seed = 1;
	ft_rrand(1, seed, 0, 0);
}

int	ft_rand(int a, int b)
{
	unsigned int	umin;
	unsigned int	umax;

	if (a == b)
		return (a);
	if (a > b)
	{
		a += b;
		b = a - b;
		a = a - b;
	}
	if (a < 0)
	{
		umin = -a;
		umax = b + umin;
		return (ft_rrand(0, 0, 0, umax) - umin);
	}
	return (ft_rrand(0, 0, a, b));
}
