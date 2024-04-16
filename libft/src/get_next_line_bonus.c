/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:16:48 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/14 17:33:23 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	**ft_free_gnl(int fd, char *str)
{
	while (str)
	{
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (NULL);
}

static void	change_str(char **str, char *cutstr)
{
	free(*str);
	*str = cutstr;
	if (ft_strlentc(*str, 0) == 0)
	{
		free(*str);
		*str = NULL;
	}
}

static char	*truncate_str(char **str)
{
	char	*cutstr;
	char	*line;
	int		start;
	int		has_n;

	if (!*str || !**str)
		return (NULL);
	has_n = !(ft_strlentc(*str, 0) == ft_strlentc(*str, '\n'));
	start = ft_strlentc(*str, '\n') + has_n;
	cutstr = ft_calloc(sizeof(char), ft_strlentc(*str + start, 0) + 1);
	if (!cutstr)
		return (NULL);
	line = (char *)malloc(sizeof(char) * start + 1);
	if (!line)
	{
		free(cutstr);
		return (NULL);
	}
	ft_strncpy(line, *str, start + 1);
	ft_strncpy(cutstr, *str + start, ft_strlentc(*str + start, 0) + 1);
	change_str(str, cutstr);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*str[1024] = {0};
	char		buffer[BUFFER_SIZE + 1];
	char		*tmp;
	ssize_t		save;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (ft_strlentc(str[fd], 0) == ft_strlentc(str[fd], '\n'))
	{
		ft_bzero(buffer, BUFFER_SIZE + 1);
		save = read(fd, buffer, BUFFER_SIZE);
		if (save <= 0)
			break ;
		buffer[save] = 0;
		tmp = str[fd];
		str[fd] = ft_strjoin(str[fd], buffer);
		if (tmp)
			free(tmp);
		if (!str[fd])
			return (NULL);
	}
	return (truncate_str(&str[fd]));
}
