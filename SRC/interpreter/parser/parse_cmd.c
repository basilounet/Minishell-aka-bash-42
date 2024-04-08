/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangouil <gangouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:17:52 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/08 13:17:52 by gangouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

static void	redlist_add(t_node *node, t_tokens **tokens)
{
	if (node->type == T_CMD)
		ft_tokadd_back(&node->cmd.redirects, *tokens);
	else
		ft_tokadd_back(&node->tree.redirects, *tokens);
	ft_tokpop(tokens);
}

int	parse_redlist(t_node *node, t_tokens **tokens)
{
	e_symbol	symbol;

	if (*tokens && is_symbol_set(4, 0, (*tokens)->symbol, T_APPEND, T_HEREDOC,
			T_INPUT, T_OUTPUT))
	{
		symbol = (*tokens)->symbol;
		free(ft_tokpop(tokens));
		if (*tokens && (*tokens)->symbol != T_ARG)
		{
			perr(2, 3, "baseshell: syntax error near unexpected token `", \
				symbol_to_char(*tokens), "'");
			return (0);
		}
		if (!*tokens)
		{
			perr(2, 1, "baseshell: syntax error near unexpected \
				token `newline'");
			return (0);
		}
		redlist_add(node, tokens);
		if (parse_redlist(node, tokens) == 0)
			return (0);
	}
	return (1);
}

t_node		*parse_command(t_tokens **tokens)
{
	t_node		*node;

	if (*tokens && is_symbol_set(3, 0, (*tokens)->symbol, T_PIPE, T_AND, T_OR))
	{
		printf("baseshell: syntax error near unexpected token `%s'\n", symbol_to_char(*tokens));
		return (NULL);
	}
	if (*tokens && (*tokens)->symbol == T_LPARENTH)
		node = parse_brace(tokens);
	else
	{
		node = parse_simple_command(tokens);
		if (node && *tokens && (*tokens)->symbol == T_LPARENTH)
		{
			printf("baseshell: syntax error near unexpected token `('\n");
			free_node(node);
			return (NULL);
		}
	}
	return (node);
}

t_node   *parse_simple_command(t_tokens **tokens)
{
	t_command	cmd;
	t_node		*node;

	cmd = ft_cmdnew(NULL, NULL);
	node = ft_nodenew(T_CMD, cmd, (t_tree){0});
	if (!node)
		return (NULL);
    while (*tokens && is_symbol_set(5, 0, (*tokens)->symbol, T_APPEND,
		T_HEREDOC, T_INPUT, T_OUTPUT, T_ARG))
	{
		if ((*tokens)->symbol != T_ARG)
		{
			if (parse_redlist(node, tokens) == 0)
			{
				ft_tokclear(&cmd.args);
				free_node(node);
				return (NULL);
			}
		}
		else
			ft_tokadd_back(&cmd.args, ft_tokpop(tokens));
	}
	node->cmd.args = cmd.args;
	return (node);
}
