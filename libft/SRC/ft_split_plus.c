/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_plus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:37:51 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/14 17:32:28 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	***ft_free_split_map(char ***split)
{
	int	i;

	i = 0;
	if (!split)
		return (NULL);
	while (split[i])
	{
		ft_free_map(split[i], ft_maplen(split[i]));
		i++;
	}
	free(split);
	return (NULL);
}

char	***ft_get_split_map(char **map, char c)
{
	char	***split_map;
	int		i;

	i = 0;
	if (!map)
		return (NULL);
	split_map = ft_calloc(sizeof(char **), ft_maplen(map) + 1);
	if (!split_map)
		return (NULL);
	while (map[i])
	{
		if (map[i][ft_strlen(map[i]) - 1] == '\n')
			map[i][ft_strlen(map[i]) - 1] = c;
		split_map[i] = ft_split(map[i], c);
		if (!map[i])
			return (ft_free_split_map(split_map));
		i++;
	}
	return (split_map);
}

void	ft_print_split_map(char ***split_map)
{
	int	i;
	int	j;

	i = 0;
	if (!split_map)
		return ;
	while (split_map[i])
	{
		j = 0;
		while (split_map[i][j])
			ft_printf("\'%s\' ", split_map[i][j++]);
		i++;
		ft_printf("\n");
	}
}
