/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_outputs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:50:19 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/01 13:31:03 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parser.h>
static void	open_redirects(t_tokens *redirects)
{
	while (redirects)
	{
		if (redirects->symbol == T_OUTPUT)
			try_close_fd(open(redirects->arg, O_CREAT | O_WRONLY | O_TRUNC,
					0644));
		if (redirects->symbol == T_APPEND)
			try_close_fd(open(redirects->arg, O_CREAT | O_WRONLY | O_APPEND,
					0777));
		redirects = redirects->next;
	}
}

void	open_all_outputs(t_node *node)
{
	if (!node)
		return ;
	if (node->type == T_TREE)
	{
		open_redirects(node->tree.redirects);
		open_all_outputs(node->tree.left);
		open_all_outputs(node->tree.right);
	}
	else
		open_redirects(node->cmd.redirects);
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
		update_outputs(node->tree.left);
		update_outputs(node->tree.right);
	}
}
