/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:36:42 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/16 14:00:53 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <stdlib.h>

t_node	*ft_nodenew(t_type type, t_command cmd, t_tree tree)
{
	t_node	*stack;

	stack = ft_calloc(sizeof(t_node), 1);
	if (!stack)
		return (NULL);
	stack->type = type;
	if (type == T_CMD)
		stack->cmd = cmd;
	else
		stack->tree = tree;
	return (stack);
}

t_command	ft_cmdnew(t_tokens *args, t_tokens *redirects)
{
	t_command	cmd;

	cmd.args = args;
	cmd.redirects = redirects;
	cmd.char_args = NULL;
	return (cmd);
}

t_node	*free_node(t_node *node)
{
	if (!node)
		return (NULL);
	if (node->type == T_CMD)
	{
		ft_tokclear(&node->cmd.args);
		ft_tokclear(&node->cmd.redirects);
		if (node->cmd.char_args)
			free(node->cmd.char_args);
		node->cmd.args = NULL;
		node->cmd.redirects = NULL;
		node->cmd.char_args = NULL;
		free(node);
		return (NULL);
	}
	ft_tokclear(&node->tree.redirects);
	if (node->tree.left)
		free_node(node->tree.left);
	if (node->tree.right)
		free_node(node->tree.right);
	node->tree.redirects = NULL;
	node->tree.left = NULL;
	node->tree.right = NULL;
	free(node);
	return (NULL);
}

t_node	*ft_treenew(t_symbol ope, t_node *left, t_node *right, t_tokens *redirs)
{
	t_tree	stack;
	t_node	*node;

	stack.operator = ope;
	stack.left = left;
	stack.right = right;
	stack.redirects = redirs;
	node = ft_nodenew(T_TREE, (t_command){}, stack);
	if (!node)
	{
		if (left)
			free_node(left);
		if (right)
			free_node(right);
		ft_tokclear(&redirs);
		return (NULL);
	}
	return (node);
}
