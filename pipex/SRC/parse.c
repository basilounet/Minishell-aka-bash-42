/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:35:20 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/23 18:20:15 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <pipex.h>

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

void	check_access(t_px *px, int ac, t_tokens *tokens)
{
	t_tokens	*tmp;
	int			i;

	i = -1;
	tmp = tokens;
	while (++i < ac && tmp)
	{
		if (!tmp->arg)
			error(px, MALLOC_ERROR);
		ft_printf("%s\n", tmp->arg);
		if (tmp->arg[0] == 0)
			error(px, PATH_NOT_FOUND);
		check_command(px, tmp->arg, i);
		tmp = tmp->next;
	}
}

t_px	parse(t_tokens *tokens, t_tokens *env)
{
	t_tokens	*tmp;
	t_px		px;

	init_px(&px);
	tmp = env;
	if (ft_toksize(tokens) < 3)
		error(&px, INVALID_AC_AMOUNT);
	while (tmp && ft_strncmp(tmp->arg, "PATH=", 5))
		tmp = tmp->next;
	if (!tmp)
		error(&px, PATH_NOT_FOUND);
	px.env = ft_split(tmp->arg + 5, ':');
	if (!px.env)
		error(&px, MALLOC_ERROR);
	px.total_cmd = ft_toksize(tokens) - 2;
	px.cmd = ft_calloc(sizeof(char **), px.total_cmd + 1);
	px.pid = ft_calloc(sizeof(pid_t), px.total_cmd + 1);
	if (!px.cmd || !px.pid)
		error(&px, MALLOC_ERROR);
	check_access(&px, px.total_cmd, tokens->next);
	return (px);
}
