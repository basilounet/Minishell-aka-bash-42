/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_outputs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:50:19 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/24 15:33:48 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_input(t_ms *ms, t_tokens *token)
{
	int	fd;

	if (!token || !token->arg)
	{
		ms->exit_code = 1;
		return (1);
	}
	if (token->symbol == T_OUTPUT)
		fd = open(token->arg, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (token->symbol == T_APPEND)
		fd = open(token->arg, O_CREAT | O_WRONLY | O_APPEND, 0777);
	else
		fd = open(token->arg, O_RDONLY);
	if (fd < 0)
	{
		perr((t_perr){ms, 1, 3, 1}, token->arg, ": ", strerror(errno));
		return (1);
	}
	close(fd);
	return (0);
}

void	expand_here_doc(t_ms *ms, t_tokens *token)
{
	char		*str;
	char		**map;
	int			fd;
	int			i;
	t_expand	exp_var;

	map = ft_get_map_fd(token->arg);
	if (!map)
		return ;
	fd = open(token->arg, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_free_map(map, ft_maplen(map));
		return ;
	}
	i = 0;
	while (map[i])
	{
		exp_var = expand_var(ms, map[i++], (t_expand_args){1, 0, 1, 0, 0});
		str = exp_var.line;
		ft_putstr_fd(str, fd);
		ft_free_ptr(1, str);
	}
	close(fd);
	ft_free_map(map, ft_maplen(map));
}

void	update_outputs(t_node *node)
{
	t_tokens	*output;

	if (!node)
		return ;
	if (node->type == T_TREE)
	{
		output = get_output_tok(node->tree.redirects);
		if (output && output->symbol == T_FINAL_OUTPUT)
			output->symbol = T_FINAL_APPEND;
		if (node->tree.operator != T_PIPE)
			add_redirect_node(node->tree.left, output);
		add_redirect_node(node->tree.right, output);
	}
}
