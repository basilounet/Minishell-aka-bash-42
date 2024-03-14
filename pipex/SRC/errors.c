/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:47:19 by bvasseur          #+#    #+#             */
/*   Updated: 2024/02/26 18:24:52 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	pipe_func_error(t_px *px, int input_fd[2], int output_fd[2],
		int original_files[2])
{
	close(input_fd[READ]);
	close(input_fd[WRITE]);
	close(output_fd[READ]);
	close(output_fd[WRITE]);
	close(original_files[READ]);
	close(original_files[WRITE]);
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
		write(2, "[ ! ERROR ! ] The path was not found / command not found\n",
			57);
	else if (name == FILE_ERROR)
		write(2, "[ ! ERROR ! ] An error occured with the files\n", 46);
	else if (name == FORK_ERROR)
		write(2, "[ ! ERROR ! ] The fork failed\n", 30);
	else if (name == ENV_ERROR)
		write(2, "[ ! ERROR ! ] One of the built-in functions malfunctioned\n",
			58);
	exit(name);
}
