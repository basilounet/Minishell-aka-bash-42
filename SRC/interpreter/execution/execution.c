/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:18:03 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/24 22:19:07 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parser.h>
#include <pipex.h>


int	node_has_input(t_node *node)
{
	if (node->type == T_TREE)
		return (node->tree.redirects != NULL);
	return (node->cmd.redirects != NULL);
}

int	update_inputs(t_node *node, t_tokens **redirects)
{
	//print_node(node, 0);
	//printf("\n");
	if (node->type == T_TREE)
	{
		if (has_input(node->tree.redirects))
			redirects = &node->tree.redirects;
		if (node_has_input(node->tree.left))
			update_inputs(node->tree.left, NULL);
		if (node_has_input(node->tree.right))
			update_inputs(node->tree.right, NULL);
		if (!node_has_input(node->tree.left))
			update_inputs(node->tree.left, redirects);
		else if (!node_has_input(node->tree.right))
			update_inputs(node->tree.right, redirects);
	}
	else if (node->type == T_CMD && redirects && *redirects && !has_input(node->cmd.redirects))
	{
		ft_tokadd_front(&node->cmd.redirects, ft_toknew(get_input_tok(*redirects)->symbol, NULL));
		get_input_tok(node->cmd.redirects)->arg = ft_strdup(get_input_tok(*redirects)->arg);
		return (1);
	}
	return (0);
}

void	execute_node(t_ms *ms, t_node *node)
{
	(void)ms;
	if (!node)
		return ;
	update_inputs(node, NULL);
}

/*
((cat && cat) < b < b < b && cat) < c
((cat && cat) && cat) < c
(( cat && cat ) < b && ( echo o && ( cat )) && ( rev )) < c
*/