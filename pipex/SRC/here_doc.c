/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:25:27 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/14 14:50:58 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	print_heredoc(t_px *px)
{
	int	i;

	i = -1;
	while (++i < px->total_cmd)
		ft_printf("pipe ");
	ft_printf("heredoc> ");
}

void	get_new_file(t_px *px, char *stop)
{
	char	*line;
	int		fd;

	if (!stop)
		error(px, MALLOC_ERROR);
	fd = open("here_doc", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		error(px, FILE_ERROR);
	print_heredoc(px);
	line = get_next_line(0);
	while (ft_strncmp(line, stop, ft_strlen(stop)))
	{
		ft_putstr_fd(line, fd);
		print_heredoc(px);
		free(line);
		line = get_next_line(0);
	}
	close(fd);
	free(stop);
	if (line)
		free(line);
}

void	here_doc(int ac, char **av, char **env, int is_append)
{
	t_px	px;
	int		input_files[2];

	px = parse(ac - 1, av + 1, env);
	px.is_append = is_append;
	get_new_file(&px, ft_strjoin(av[1], "\n"));
	create_inputs(ac, av, &px, input_files);
	if (ac == 4)
		sole_pipe(&px, input_files);
	else
		all_pipes(&px, input_files);
	unlink("here_doc");
	unleak(&px);
	exit(0);
}
