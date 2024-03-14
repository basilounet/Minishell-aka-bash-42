/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:32:37 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/14 17:44:02 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>
#include <libft.h>

void	create_inputs(int ac, char **av, t_px *px, int input_files[2])
{
	if (!ft_strncmp(av[0], "STDIN", 6))
		input_files[READ] = STDIN_FILENO;
	else
		input_files[READ] = open(av[0], O_RDONLY);
	if (!ft_strncmp(av[ac - 1], "STDOUT", 7))
		input_files[WRITE] = STDOUT_FILENO;
	else if (px->is_append)
		input_files[WRITE] = open(av[ac - 1], O_CREAT | O_RDWR | O_APPEND,
				0777);
	else
		input_files[WRITE] = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (input_files[READ] < 0 || input_files[WRITE] < 0)
	{
		try_close_fd(input_files[0]);
		try_close_fd(input_files[1]);
		error(px, FILE_ERROR);
	}
}

int	pipex(int ac, char **av, char **env, int is_append)
{
	t_px	px;
	int		input_files[2];

	if (ac > 1 && !ft_strncmp(av[0], "here_doc", 8))
		here_doc(ac, av, env, is_append);
	px = parse(ac, av, env);
	px.is_append = is_append;
	create_inputs(ac, av, &px, input_files);
	if (ac == 3)
		sole_pipe(&px, input_files);
	else
		all_pipes(&px, input_files);
	unleak(&px);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	pipex(ac - 1, av + 1, env, 0);
}
