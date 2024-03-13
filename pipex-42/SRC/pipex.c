/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:32:37 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/13 14:24:02 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	pipex(int ac, char **av, char **env)
{
	t_px	px;
	int		input_files[2];

	if (ac > 1 && !ft_strncmp(av[0], "here_doc", 8))
		here_doc(ac, av, env);
	px = parse(ac, av, env);
	input_files[READ] = open(av[0], O_RDONLY);
	input_files[WRITE] = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (input_files[READ] < 0 || input_files[WRITE] < 0)
	{
		if (input_files[0] >= 0)
			close(input_files[0]);
		if (input_files[1] >= 0)
			close(input_files[1]);
		error(&px, FILE_ERROR);
	}
	else if (ac == 3)
		sole_pipe(&px, input_files);
	else
		all_pipes(&px, input_files);
	unleak(&px);
	return (0);
}

char	*france_pattern(size_t i, size_t len)
{
	if (i <= len * 1 / 3)
		return (BLUE);
	else if (i <= len * 2 / 3)
		return (WHITE);
	else if (i <= len)
		return (RED);
	return (BASE_COLOR);
}

char	*moving_france_pattern(size_t i, size_t len)
{
	static size_t	j = 0;

	if (i >= len - 1)
		j = (j + 1) % len;
	i = (i + j) % len;
	if (i <= len * 1 / 3)
		return (BLUE);
	else if (i <= len * 2 / 3)
		return (WHITE);
	else if (i <= len)
		return (RED);
	return (BASE_COLOR);
}

char	*rainbow_pattern(size_t i, size_t len)
{
	if (i <= len * 1 / 5)
		return (MAGENTA);
	else if (i <= len * 2 / 5)
		return (BLUE);
	else if (i <= len * 3 / 5)
		return (GREEN);
	else if (i <= len * 4 / 5)
		return (YELLOW);
	else if (i <= len)
		return (RED);
	return (BASE_COLOR);
}

char	*moving_rainbow_pattern(size_t i, size_t len)
{
	static size_t	j = 0;

	if (i >= len - 1)
		j = (j + 1) % len;
	i = (i + j) % len;
	if (i <= len * 1 / 5)
		return (MAGENTA);
	else if (i <= len * 2 / 5)
		return (BLUE);
	else if (i <= len * 3 / 5)
		return (GREEN);
	else if (i <= len * 4 / 5)
		return (YELLOW);
	else if (i <= len)
		return (RED);
	return (BASE_COLOR);
}

void	print_pwd(char *(*color_pattern)(size_t, size_t))
{
	char	*pwd;
	size_t	len;
	size_t	i;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return ;
	i = 0;
	len = ft_strlen(pwd);
	while (pwd[i])
	{
		ft_putstr(color_pattern(i, len));
		ft_putchar(pwd[i]);
		i++;
	}
	ft_putstr("\033[0m");
	free(pwd);
}

#include <unistd.h>

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	int i = 0;
	while (i < 10000)
	{
		write(1, "\E[H\E[2J", 7);
		print_pwd(&moving_rainbow_pattern);
		usleep(50000);
		i++;
	}
}
