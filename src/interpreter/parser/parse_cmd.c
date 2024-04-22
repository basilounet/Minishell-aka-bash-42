/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:17:52 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/19 19:11:08 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	redlist_add(t_ms *ms, t_node *node, t_tokens **tokens, t_symbol sym)
{
	set_interactive_mode(0);
	if (sym == T_HEREDOC && g_sig != SIGINT)
	{
		if ((ft_countc((*tokens)->arg, '\"') || ft_countc((*tokens)->arg,
					'\'')))
			(*tokens)->symbol = T_INPUT;
		open_heredoc(ms, &(*tokens)->arg);
		free((*tokens)->arg);
		(*tokens)->arg = ft_str_reajoin("/tmp/here_doc_",
				ft_itoa(ms->heredoc_number++), 0, 1);
		if (g_sig == SIGINT)
			ms->exit_code = 130;
	}
	set_interactive_mode(1);
	if (node->type == T_CMD)
		ft_tokadd_back(&node->cmd.redirects, *tokens);
	else
		ft_tokadd_back(&node->tree.redirects, *tokens);
	ft_tokpop(tokens);
}

int	parse_redlist(t_ms *ms, t_node *node, t_tokens **tokens)
{
	t_symbol	symbol;

	if (*tokens && is_symbol_set(4, 0, (*tokens)->symbol, T_APPEND, T_HEREDOC,
			T_INPUT, T_OUTPUT))
	{
		symbol = (*tokens)->symbol;
		free(ft_tokpop(tokens));
		if (*tokens && (*tokens)->symbol != T_ARG)
		{
			perr((t_perr){ms, 2, 4, 1}, SYN_ERR, "`", symbol_to_char(*tokens),
				"'");
			return (0);
		}
		if (!*tokens)
		{
			perr((t_perr){ms, 2, 2, 1}, SYN_ERR, "`newline'");
			return (0);
		}
		(*tokens)->symbol = symbol;
		redlist_add(ms, node, tokens, symbol);
		if (parse_redlist(ms, node, tokens) == 0)
			return (0);
	}
	return (1);
}

t_node	*parse_command(t_ms *ms, t_tokens **tokens)
{
	t_node	*node;

	if (*tokens && is_symbol_set(3, 0, (*tokens)->symbol, T_PIPE, T_AND, T_OR))
	{
		perr((t_perr){ms, 2, 4, 1}, SYN_ERR, "`", symbol_to_char(*tokens), "'");
		return (NULL);
	}
	if (*tokens && (*tokens)->symbol == T_LPARENTH)
		node = parse_brace(ms, tokens);
	else
	{
		node = parse_simple_command(ms, tokens);
		if (node && *tokens && (*tokens)->symbol == T_LPARENTH)
		{
			perr((t_perr){ms, 2, 2, 1}, SYN_ERR, "`('");
			free_node(node);
			return (NULL);
		}
	}
	return (node);
}

t_node	*parse_simple_command(t_ms *ms, t_tokens **tokens)
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
			if (parse_redlist(ms, node, tokens) == 0)
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
