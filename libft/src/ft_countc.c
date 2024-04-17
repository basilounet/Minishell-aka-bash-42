/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:54:01 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/18 13:36:58 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

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

size_t	ft_countcn(char *str, char c, int n)
{
	size_t	count;
	int		i;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i] && i < n)
		if (str[i++] == c)
			count++;
	return (count);
}

size_t	ft_countcnm(char *str, char c, int n, char *mask)
{
	size_t	count;
	int		i;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i] && i < n)
	{
		if (mask[i] != '2' && str[i] == c)
			count++;
		i++;
	}
	return (count);
}
