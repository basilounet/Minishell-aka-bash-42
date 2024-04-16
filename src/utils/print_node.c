/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:04:41 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/16 11:05:16 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*sym_to_char(t_symbol symbol)
{
	if (symbol == T_PIPE)
		return ("|");
	if (symbol == T_INPUT)
		return ("<");
	if (symbol == T_HEREDOC)
		return ("<<");
	if (symbol == T_OUTPUT)
		return (">");
	if (symbol == T_APPEND)
		return (">>");
	if (symbol == T_LPARENTH)
		return ("(");
	if (symbol == T_RPARENTH)
		return (")");
	if (symbol == T_OR)
		return ("||");
	if (symbol == T_AND)
		return ("&&");
	return (NULL);
}

static void	print_pad(int depth)
{
	while (depth)
	{
		printf("|  ");
		depth--;
	}
}

void	print_tokens(t_tokens *tokens, int depth)
{
	while (tokens)
	{
		print_pad(depth);
		printf("symbol = %u, arg = \"%s\"\n", tokens->symbol, tokens->arg);
		tokens = tokens->next;
	}
}

void	print_node(t_node *node, int depth)
{
	if (!node)
		return ;
	if (node->type == T_CMD)
	{
		print_pad(depth);
		printf("<cmd>\n");
		print_pad(++depth);
		printf("<args>\n");
		print_tokens(node->cmd.args, depth);
		print_pad(++depth - 1);
		printf("<redirects>\n");
		print_tokens(node->cmd.redirects, depth);
	}
	if (node->type == T_TREE)
	{
		print_pad(depth);
		printf("<tree>\n");
		print_pad(++depth);
		printf("operator = %s\n", sym_to_char(node->tree.operator));
		print_node(node->tree.left, depth + 1);
		print_node(node->tree.right, depth + 1);
		print_pad(depth);
		printf("<redirects>\n");
		print_tokens(node->tree.redirects, depth);
	}
}
