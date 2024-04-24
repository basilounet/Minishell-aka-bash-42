/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:51:28 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/23 13:36:52 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	close_all_fds(void)
{
	int	err;
	int	i;

	err = errno;
	i = 3;
	while (i < 1024)
		try_close_fd(i++);
	errno = err;
}

void	try_close_fd(int fd)
{
	if (fd > 2)
		close(fd);
}
