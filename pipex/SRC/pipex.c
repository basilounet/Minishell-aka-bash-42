/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:32:37 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/23 18:19:47 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <pipex.h>
#include <parser.h>

void	create_inputs(t_tokens *tokens, t_px *px, int input_files[2])
{
	if (!ft_strncmp(tokens->arg, "STDIN", 6))
		input_files[READ] = STDIN_FILENO;
	else
		input_files[READ] = open(tokens->arg, O_RDONLY);
	if (!ft_strncmp(ft_toklast(tokens)->arg, "STDOUT", 7))
		input_files[WRITE] = STDOUT_FILENO;
	else if (px->is_append)
		input_files[WRITE] = open(ft_toklast(tokens)->arg, O_CREAT | O_WRONLY | O_APPEND,
				0777);
	else
		input_files[WRITE] = open(ft_toklast(tokens)->arg, O_CREAT | O_WRONLY | O_TRUNC,
				0644);
	if (input_files[READ] < 0 || input_files[WRITE] < 0)
	{
		try_close_fd(input_files[0]);
		try_close_fd(input_files[1]);
		error(px, FILE_ERROR);
	}
}

int	pipex(t_tokens *tokens, t_tokens *env, int is_append)
{
	t_px	px;
	int		input_files[2];

	px = parse(tokens, env);
	px.is_append = is_append;
	create_inputs(tokens, &px, input_files);
	if (ft_toksize(tokens) == 3)
		sole_pipe(&px, input_files);
	else
		all_pipes(&px, input_files);
	unleak(&px);
	return (0);
}
