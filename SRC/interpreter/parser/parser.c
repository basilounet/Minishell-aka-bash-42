/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangouil <gangouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:07:23 by gangouil          #+#    #+#             */
/*   Updated: 2024/03/20 16:07:23 by gangouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

static char	*symbol_to_char(t_tokens *token)
{
	if (token->symbol == T_ARG)
		return (token->arg);
	if (token->symbol == T_PIPE)
		return ("|");
	if (token->symbol == T_INPUT)
		return ("<");
	if (token->symbol == T_HEREDOC)
		return ("<<");
	if (token->symbol == T_OUTPUT)
		return (">");
	if (token->symbol == T_APPEND)
		return (">>");
	if (token->symbol == T_LPARENTH)
		return ("(");
	if (token->symbol == T_RPARENTH)
		return (")");
	if (token->symbol == T_OR)
		return ("||");
	if (token->symbol == T_AND)
		return ("&&");
	return (NULL);
}

static int	is_symbol_set(int n, int exclude, e_symbol compared, ...)
{
	int		current_arg;
	va_list	args;

	va_start(args, compared);
	while (n)
	{
		current_arg = va_arg(args, int);
		if (exclude == 0 && (int)compared == current_arg)
		{
			va_end(args);
			return (1);
		}
		if (exclude == 1 && (int)compared == current_arg)
		{
			va_end(args);
			return (0);
		}
		n--;
	}
	va_end(args);
	return (exclude);
}

static int	parenth_check(t_tokens *tokens)
{
	int	balance;

	balance = 0;
	while (tokens)
	{
		if (balance < 0)
			break;
		if (tokens->symbol == T_LPARENTH)
			balance++;
		if (tokens->symbol == T_RPARENTH)
			balance--;
		tokens = tokens->next;
	}
	if (balance > 0 || balance < 0)
	{
		if (balance > 0)
			printf("baseshell: syntax error near unexpected token `('\n");
		if (balance < 0)
			printf("baseshell: syntax error near unexpected token `)'\n");
		return (0);
	}
	return (1);
}

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
				ft_tokclear(cmd.args);
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

t_node *parse_brace(t_tokens **tokens)
{
	t_node	*node;

	free(ft_tokpop(tokens));
	if (*tokens && (*tokens)->symbol == T_RPARENTH)
	{
		printf("baseshell: syntax error near unexpected token `)'\n");
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
			printf("baseshell: syntax error near unexpected token `%s'\n", symbol_to_char(*tokens));
			return (0);
		}
		if (!*tokens)
		{
			printf("baseshell: syntax error near unexpected token `newline'\n");
			return (0);
		}
		(*tokens)->symbol = symbol;
		if (node->type == T_CMD)
			ft_tokadd_back(&node->cmd.redirects, *tokens);
		else
			ft_tokadd_back(&node->tree.redirects, *tokens);
		ft_tokpop(tokens);
		if (parse_redlist(node, tokens) == 0)
			return (0);
	}
	return (1);
}