/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:54:18 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/09 19:00:52 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	sole_pipe(t_px *px, int input_files[2])
{
	int	pid;

	pid = fork();
	if (pid < 0)
		error(px, FORK_ERROR);
	if (pid == 0)
		pipex_child(px, input_files, input_files, input_files);
	else
	{
		try_close_fd(input_files[READ]);
		try_close_fd(input_files[WRITE]);
		wait(NULL);
	}
}

void	first_pipe(t_px *px, int input_files[2], int new_pipe[2])
{
	int	pid;

	if (pipe(new_pipe) == -1)
		error(px, ENV_ERROR);
	pid = fork();
	px->pid[0] = pid;
	if (pid < 0)
		error(px, FORK_ERROR);
	if (pid == 0)
		pipex_child(px, input_files, new_pipe, input_files);
	else
	{
		try_close_fd(input_files[READ]);
		try_close_fd(new_pipe[WRITE]);
	}
}

void	last_pipe(t_px *px, int original_files[2], int new_pipe[2])
{
	int	pid;

	pid = fork();
	px->pid[px->total_cmd - 1] = pid;
	if (pid < 0)
		error(px, FORK_ERROR);
	if (pid == 0)
		pipex_child(px, new_pipe, original_files, original_files);
	else
	{
		try_close_fd(original_files[WRITE]);
		try_close_fd(new_pipe[READ]);
	}
}

void	all_pipes(t_px *px, int input_files[2])
{
	int		right_pipe[2];
	int		left_pipe[2];
	pid_t	pid;
	int		i;

	first_pipe(px, input_files, right_pipe);
	while (++px->index <= px->total_cmd - 2)
	{
		left_pipe[0] = right_pipe[0];
		left_pipe[1] = right_pipe[1];
		if (pipe(right_pipe) == -1)
			pipe_func_error(px, left_pipe, right_pipe, input_files);
		pid = fork();
		px->pid[px->index] = pid;
		if (pid < 0)
			error(px, FORK_ERROR);
		if (pid == 0)
			pipex_child(px, left_pipe, right_pipe, input_files);
		else
			pipex_parent(px, left_pipe, right_pipe);
	}
	last_pipe(px, input_files, right_pipe);
	i = 0;
	while (i < px->total_cmd)
		waitpid(px->pid[i++], NULL, 0);
}
