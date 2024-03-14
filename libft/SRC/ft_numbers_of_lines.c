/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbers_of_lines.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 21:55:31 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/14 17:31:45 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_numbers_of_lines(char *path)
{
	size_t	count;
	char	*str;
	int		fd;

	fd = open(path, O_RDONLY);
	count = 0;
	str = get_next_line(fd);
	while (str)
	{
		count++;
		if (str)
			free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (count);
}
