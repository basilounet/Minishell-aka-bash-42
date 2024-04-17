/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:45:27 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/17 11:29:14 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	**ft_free_map(char **map, size_t len)
{
	size_t	i;

	i = 0;
	if (!map)
		return (NULL);
	while (i < len)
	{
		if (map[i++])
		{
			free(map[i - 1]);
			map[i - 1] = NULL;
		}
	}
	free(map);
	map = NULL;
	return (NULL);
}

size_t	ft_maplen(char **map)
{
	size_t	i;

	i = 0;
	if (!map)
		return (i);
	while (map[i])
		i++;
	return (i);
}

char	**ft_mapcpy(char **original, size_t len)
{
	char	**map;
	size_t	i;

	i = 0;
	if (!original)
		return (NULL);
	map = ft_calloc(sizeof(char *), len + 1);
	if (!map)
		return (NULL);
	while (i < len)
	{
		map[i] = ft_strdup(original[i]);
		if (!map[i])
			return (ft_free_map(map, i));
		i++;
	}
	return (map);
}

void	ft_print_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		ft_printf("%s\n", map[i]);
		i++;
	}
}

char	**ft_get_map_fd(char *path)
{
	char	**map;
	char	*str;
	int		fd;
	int		i;

	i = 0;
	fd = open(path, O_RDONLY);
	map = ft_calloc(sizeof(char **), ft_numbers_of_lines(path) + 1);
	if (!map)
		return (NULL);
	str = get_next_line(fd);
	while (str)
	{
		map[i] = ft_calloc(sizeof(char *), ft_strlen(str) + 1);
		if (!map[i])
		{
			ft_free_map(map, i);
			return (ft_free_gnl(fd, str));
		}
		ft_strncpy(map[i++], str, ft_strlen(str) + 1);
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (map);
}
