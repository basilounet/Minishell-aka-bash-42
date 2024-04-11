/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_outputs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:50:19 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/11 15:43:23 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	check_input(t_ms *ms, t_tokens *token)
{
	int	fd;

	if (!token || !token->arg)
	{
		ms->exit_code = 1;
		return ;
	}
	fd = open(token->arg, O_RDONLY);
	if (fd < 0)
	{
		ms->exit_code = perr(1, 1, 1, strerror(errno));
		return ;
	}
	close(fd);
}

void	transform_heredoc_into_inputs(t_node *node, char *name)
{
	t_tokens	*tmp_tok;

	tmp_tok = NULL;
	if (!node)
		return ;
	if (node->type == T_TREE)
	{
		transform_heredoc_into_inputs(node->tree.left, name);
		transform_heredoc_into_inputs(node->tree.right, name);
		tmp_tok = node->tree.redirects;
	}
	else
		tmp_tok = node->cmd.redirects;
	while (tmp_tok)
	{
		if (tmp_tok->symbol == T_HEREDOC && !ft_strcmp(tmp_tok->arg, name))
			tmp_tok->symbol = T_INPUT;
		tmp_tok = tmp_tok->next;
	}
}

void	expand_here_doc(t_ms *ms, char *name)
{
	char	*str;
	char	**map;
	int		fd;
	int		i;

	map = ft_get_map_fd(name);
	if (!map)
		return ;
	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_free_map(map, ft_maplen(map));
		return;
	}
	i = 0;
	while (map[i])
	{
		str = ft_str_reajoin(expand_var(ms->env, map[i++], (t_expand_args){1, 0,
					1}), "\n", 1, 0);
		ft_putstr_fd(str, fd);
		ft_free_ptr(1, str);
	}
	close(fd);
	ft_free_map(map, ft_maplen(map));
	transform_heredoc_into_inputs(ms->root_node, name);
}

void	update_outputs(t_node *node)
{
	if (!node)
		return ;
	if (node->type == T_TREE)
	{
		if (node->tree.operator != T_PIPE)
			add_redirect_node(node->tree.left,
				get_output_tok(node->tree.redirects));
		add_redirect_node(node->tree.right,
			get_output_tok(node->tree.redirects));
	}
}
