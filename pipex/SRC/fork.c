/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 02:50:01 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/14 14:50:54 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	try_close_fd(int fd)
{
	if (fd > 2)
		close(fd);
}

void	pipex_child(t_px *px, int input_fd[2], int output_fd[2],
		int original_files[2])
{
	int	error_occured;

	error_occured = 0;
	if (dup2(input_fd[READ], STDIN_FILENO) == -1 || dup2(output_fd[WRITE],
			STDOUT_FILENO) == -1)
		error_occured = 1;
	try_close_fd(input_fd[READ]);
	try_close_fd(input_fd[WRITE]);
	try_close_fd(output_fd[READ]);
	try_close_fd(output_fd[WRITE]);
	try_close_fd(original_files[READ]);
	try_close_fd(original_files[WRITE]);
	if (error_occured)
		error(px, ENV_ERROR);
	if (execve(px->cmd[px->index][0], px->cmd[px->index], px->env) == -1)
		error(px, ENV_ERROR);
}

void	pipex_parent(t_px *px, int old_pipe[2], int new_pipe[2])
{
	(void)px;
	try_close_fd(new_pipe[WRITE]);
	try_close_fd(old_pipe[READ]);
}
