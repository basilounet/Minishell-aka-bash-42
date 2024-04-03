/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:14:40 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/03 17:21:00 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	transform_to_chars(t_node *node)
{
	int	i;

	if (node->type == T_TREE)
	{
		transform_to_chars(node->tree.left);
		transform_to_chars(node->tree.right);
	}
	else
	{
		i = 0;
		node->cmd.char_args = ft_calloc(sizeof(char *),
				ft_toksize(node->cmd.args) + 1);
		if (!node->cmd.char_args)
			return ;
		while (node->cmd.args)
		{
			node->cmd.char_args[i++] = node->cmd.args->arg;
			node->cmd.args = node->cmd.args->next;
		}
	}
}

void	expand_args(t_ms *ms, t_node *node)
{
	t_tokens	*tmp_tok;
	char		*tmp_char;

	if (node->type == T_TREE)
		return ;
	tmp_tok = node->cmd.args;
	while (tmp_tok)
	{
		tmp_char = tmp_tok->arg;
		tmp_tok->arg = expand_var(ms->env, tmp_char, 1, 1);
		if (should_split_ifs(tmp_char) && ft_countc(tmp_char, '$') != 0)
			split_ifs(&tmp_tok);
		free(tmp_char);
		if (tmp_tok)
			tmp_tok = tmp_tok->next;
	}
}

void	expand_redirects(t_ms *ms, t_node *node)
{
	t_tokens	*tmp_tok;
	char		*tmp_char;

	if (node->type == T_TREE)
		tmp_tok = node->tree.redirects;
	else
		tmp_tok = node->cmd.redirects;
	while (tmp_tok)
	{
		tmp_char = tmp_tok->arg;
		tmp_tok->arg = expand_var(ms->env, tmp_char, 1, 1);
		if (should_split_ifs(tmp_char) && ft_countc(tmp_char, '$') != 0)
		{
			ft_printf("baseshell: ambiguous redirect\n");
			free(tmp_char);
			/////////////////////////////////////////////////////////////////////////////
			return ;
		}
		if (tmp_tok)
			tmp_tok = tmp_tok->next;
	}
}

void	prepare_and_execute(t_ms *ms, t_node *node)
{
	open_all_outputs(ms, node);
	update_inputs(node);
	update_outputs(node);
	expand_args(ms, node);
	expand_redirects(ms, node);
	print_node(node, 0);
	execute_node(ms, node, 0);
}
