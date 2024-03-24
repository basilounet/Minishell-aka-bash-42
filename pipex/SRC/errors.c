/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:47:19 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/23 18:00:41 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	pipe_func_error(t_px *px, int input_fd[2], int output_fd[2],
		int original_files[2])
{
	try_close_fd(input_fd[READ]);
	try_close_fd(input_fd[WRITE]);
	try_close_fd(output_fd[READ]);
	try_close_fd(output_fd[WRITE]);
	try_close_fd(original_files[READ]);
	try_close_fd(original_files[WRITE]);
	error(px, ENV_ERROR);
}

void	error(t_px *px, enum e_errors name)
{
	write(2, "Error\n", 6);
	unleak(px);
	if (name == MALLOC_ERROR)
		write(2, "[ ! ERROR ! ] A malloc error occured\n", 37);
	else if (name == INVALID_AC_AMOUNT)
		write(2, "[ ! ERROR ! ] Incorrect numbers of arguments\n", 45);
	else if (name == PATH_NOT_FOUND)
		write(2, "[ ! ERROR ! ] Path not found / command not found\n", 48);
	else if (name == FILE_ERROR)
		write(2, "[ ! ERROR ! ] An error occured with the files\n", 46);
	else if (name == FORK_ERROR)
		write(2, "[ ! ERROR ! ] The fork failed\n", 30);
	else if (name == ENV_ERROR)
		write(2, "[ ! ERROR ! ] One of the built-in functions malfunctioned\n",
			58);
	exit(name);
}
