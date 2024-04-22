/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangouil <gangouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:51:28 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/19 18:51:31 by gangouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	close_all_fds(t_ms *ms)
{
	int	i;

	i = 3;
	while (i < 1024)
		try_close_fd(i++);
	errno = ms->exit_code;
}

void	try_close_fd(int fd)
{
	if (fd > 2)
		close(fd);
}
