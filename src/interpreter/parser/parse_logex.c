/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_logex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:17:56 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/19 18:38:40 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_node	*parse_prompt(t_ms *ms, t_tokens **tokens)
{
	t_node	*node;

	if (!parenth_check(ms, *tokens))
		return (NULL);
	node = parse_logex(ms, tokens);
	if (node && *tokens)
	{
		perr((t_perr){ms, 2, 4, 1}, SYN_ERR, "`", symbol_to_char(*tokens), "'");
		free_node(node);
		return (NULL);
	}
	return (node);
}

t_node	*parse_logex(t_ms *ms, t_tokens **tokens)
{
	t_node		*node;
	t_node		*right;
	t_symbol	symbol;

	node = parse_pipeline(ms, tokens);
	while (node && *tokens && ((*tokens)->symbol == T_OR
			|| (*tokens)->symbol == T_AND))
	{
		symbol = (*tokens)->symbol;
		free(ft_tokpop(tokens));
		if (!*tokens)
		{
			perr((t_perr){ms, 2, 2, 1}, SYN_ERR, "`newline'");
			free_node(node);
			return (NULL);
		}
		right = parse_pipeline(ms, tokens);
		if (!right)
		{
			free_node(node);
			return (NULL);
		}
		node = ft_treenew(symbol, node, right, NULL);
	}
	return (node);
}

t_node	*parse_pipeline(t_ms *ms, t_tokens **tokens)
{
	t_node	*node;
	t_node	*right;

	node = parse_command(ms, tokens);
	if (node && *tokens && (*tokens)->symbol == T_PIPE)
	{
		free(ft_tokpop(tokens));
		if (!*tokens)
		{
			perr((t_perr){ms, 2, 2, 1}, SYN_ERR, "`newline'");
			free_node(node);
			return (NULL);
		}
		right = parse_pipeline(ms, tokens);
		if (!right)
		{
			free_node(node);
			return (NULL);
		}
		node = ft_treenew(T_PIPE, node, right, NULL);
	}
	return (node);
}

t_node	*parse_brace(t_ms *ms, t_tokens **tokens)
{
	t_node	*node;

	free(ft_tokpop(tokens));
	if (*tokens && (*tokens)->symbol == T_RPARENTH)
	{
		perr((t_perr){ms, 2, 2, 1}, SYN_ERR, "`)'");
		return (NULL);
	}
	node = parse_logex(ms, tokens);
	if (*tokens && (*tokens)->symbol == T_RPARENTH)
		free(ft_tokpop(tokens));
	if (*tokens && node && parse_redlist(ms, node, tokens) == 0)
	{
		free_node(node);
		return (NULL);
	}
	return (node);
}
