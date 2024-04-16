/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 21:42:01 by marvin            #+#    #+#             */
/*   Updated: 2024/03/14 17:31:58 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_putendl_fd(char const *s, int fd)
{
	if (s == NULL)
		s = (char *)"(null)";
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}
