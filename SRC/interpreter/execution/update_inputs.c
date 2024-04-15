/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_inputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:18:03 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/15 14:55:02 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parser.h>

void	add_redirect_node(t_node *node, t_tokens *token)
{
	t_tokens	*new_redirect;

	if (!token)
		return ;
	new_redirect = ft_toknew(token->symbol, ft_strdup(token->arg), NULL);
	if (!new_redirect)
		return ;
	if (new_redirect->symbol == T_OUTPUT)
		new_redirect->symbol = T_APPEND;
	if (node->type == T_TREE)
		ft_tokadd_front(&node->tree.redirects, new_redirect);
	else
		ft_tokadd_front(&node->cmd.redirects, new_redirect);
}

void	add_redirect_pipe(t_node *node, t_tokens *redirect)
{
	if (node->type == T_TREE && node->tree.operator == T_PIPE)
		add_redirect_pipe(node->tree.left, redirect);
	else
		add_redirect_node(node, redirect);
}

int	is_node_all_redirected(t_node *node)
{
	if (node->type == T_TREE)
	{
		if (node->tree.operator == T_OR || node->tree.operator == T_AND)
			return (is_node_all_redirected(node->tree.left)
				&& is_node_all_redirected(node->tree.right));
		else if (node->tree.operator == T_PIPE)
			return (is_node_all_redirected(node->tree.left));
	}
	return (has_input(node->cmd.redirects));
}

int	place_and(t_node *node, t_tokens *redirect)
{
	if (node->type == T_TREE && !is_node_all_redirected(node->tree.left)
		&& place_and(node->tree.left, redirect))
		return (1);
	else if (node->type == T_TREE && !is_node_all_redirected(node->tree.right)
		&& place_and(node->tree.right, redirect))
		return (1);
	else
	{
		add_redirect_node(node, redirect);
		return (1);
	}
	return (0);
}

void	update_inputs(t_node *node)
{
	if (!node)
		return ;
	if (node->type == T_TREE)
	{
		if (node->tree.operator == T_OR)
		{
			add_redirect_node(node->tree.left,
				get_input_tok(node->tree.redirects));
			add_redirect_node(node->tree.right,
				get_input_tok(node->tree.redirects));
		}
		else if (node->tree.operator == T_PIPE)
			add_redirect_pipe(node, get_input_tok(node->tree.redirects));
		else if (node->tree.operator == T_AND)
			place_and(node, get_input_tok(node->tree.redirects));
	}
}
