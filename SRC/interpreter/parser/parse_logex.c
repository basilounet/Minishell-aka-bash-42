/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_logex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangouil <gangouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:17:56 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/08 13:17:58 by gangouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

t_node	*parse_prompt(t_tokens **tokens)
{
	t_node *node;

	if (!parenth_check(*tokens))
		return (NULL);
	node = parse_logex(tokens);
	if (node && *tokens)
	{
		printf("baseshell: syntax error near unexpected token `%s'\n", symbol_to_char(*tokens));
		free_node(node);
		return (NULL);
	}
	return (node);
}

t_node	*parse_logex(t_tokens **tokens)
{
    t_node		*node;
	t_node		*right;
	e_symbol	symbol;

	node = parse_pipeline(tokens);
	while (node && *tokens && ((*tokens)->symbol == T_OR
		|| (*tokens)->symbol == T_AND))
	{
		symbol = (*tokens)->symbol;
		free(ft_tokpop(tokens));
		if (!*tokens)
		{
			printf("baseshell: syntax error near unexpected token `newline'\n");
			free_node(node);
			return (NULL);
		}
		right = parse_pipeline(tokens);
		if (!right)
		{
			free_node(node);
			return (NULL);
		}
		node = ft_treenew(symbol, node, right, NULL);
	}
	return (node);
}

t_node *parse_pipeline(t_tokens **tokens)
{
	t_node	*node;
	t_node	*right;

	node = parse_command(tokens);
	if (node && *tokens && (*tokens)->symbol == T_PIPE)
	{
		free(ft_tokpop(tokens));
		if (!*tokens)
		{
			printf("baseshell: syntax error near unexpected token `newline'\n");
			free_node(node);
			return (NULL);
		}
		right = parse_pipeline(tokens);
		if (!right)
		{
			free_node(node);
			return (NULL);
		}
		node = ft_treenew(T_PIPE, node, right, NULL);
	}
	return (node);
}

t_node *parse_brace(t_tokens **tokens)
{
	t_node	*node;

	free(ft_tokpop(tokens));
	if (*tokens && (*tokens)->symbol == T_RPARENTH)
	{
		perr(2, 1, "baseshell: syntax error near unexpected token `)'");
		return (NULL);
	}
	node = parse_logex(tokens);
	if (*tokens && (*tokens)->symbol == T_RPARENTH)
		free(ft_tokpop(tokens));
	if (*tokens && node && parse_redlist(node, tokens) == 0)
	{
		free_node(node);
		return (NULL);
	}
    return (node);
}
