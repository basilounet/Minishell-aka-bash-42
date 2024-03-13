/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:59:17 by bvasseur          #+#    #+#             */
/*   Updated: 2023/11/08 12:42:45 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_base(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	transform(char *str, char *base, int len_base)
{
	int	len_number;
	int	number;
	int	i;
	int	k;

	number = 0;
	i = 0;
	len_number = 0;
	while (is_in_base(str[len_number], base))
		len_number++;
	while (i < len_number)
	{
		k = 0;
		while (i < len_number && str[i] != base[k])
			k++;
		number += k * ft_power(len_base, len_number - 1 - i);
		i++;
	}
	return (number);
}

int	ft_atoi_base(char *str, char *base)
{
	int	i;
	int	sign;
	int	number;

	sign = 1;
	number = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\r' || str[i] == '\f')
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	number = transform(&str[i], base, ft_strlen(base));
	return (number * sign);
}
