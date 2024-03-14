/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:35:20 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/14 17:45:20 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>
#include "../includes/libft.h"

void	check_command(t_px *px, char *command, int index)
{
	char	*str;
	int		i;

	i = -1;
	px->cmd[index] = ft_split(command, ' ');
	if (!px->cmd[index])
		error(px, MALLOC_ERROR);
	if (!access(px->cmd[index][0], F_OK) && !access(px->cmd[index][0], X_OK))
		return ;
	while (px->env[++i])
	{
		str = ft_strjoin3(px->env[i], "/", px->cmd[index][0]);
		if (!str)
			error(px, MALLOC_ERROR);
		if (!access(str, F_OK) && !access(str, X_OK))
		{
			free(px->cmd[index][0]);
			px->cmd[index][0] = str;
			return ;
		}
		free(str);
	}
	error(px, PATH_NOT_FOUND);
}

void	check_access(t_px *px, int ac, char **av)
{
	int	i;

	i = -1;
	while (++i < ac)
	{
		if (av[i][0] == 0)
			error(px, PATH_NOT_FOUND);
		check_command(px, av[i], i);
	}
}

t_px	parse(int ac, char **av, char **env)
{
	t_px	px;
	int		i;

	i = 0;
	init_px(&px);
	if (ac < 3)
		error(&px, INVALID_AC_AMOUNT);
	if (!env)
		error(&px, PATH_NOT_FOUND);
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		error(&px, PATH_NOT_FOUND);
	px.env = ft_split(env[i] + 5, ':');
	if (!px.env)
		error(&px, MALLOC_ERROR);
	px.total_cmd = ac - 2;
	px.cmd = ft_calloc(sizeof(char **), px.total_cmd + 1);
	px.pid = ft_calloc(sizeof(pid_t), px.total_cmd + 1);
	if (!px.cmd || !px.pid)
		error(&px, MALLOC_ERROR);
	check_access(&px, ac - 2, av + 1);
	return (px);
}
