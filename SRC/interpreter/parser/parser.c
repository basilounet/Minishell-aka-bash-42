/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:26:51 by gangouil          #+#    #+#             */
/*   Updated: 2024/03/17 17:07:11 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

static int	is_symbol_set(int n, int exclude, e_symbol compared, ...)
{
	int		current_arg;
	va_list	args;

	va_start(args, n);
	pass = 0;
	while (n)
	{
		current_arg = va_arg(args, int);
		if (exclude == 0 && compared == current_arg)
		{
			va_end(args);
			return (1);
		}
		if (exclude == 1 && compared == current_arg)
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
			return (0); // syntax error
		if (tokens->symbol == T_LPARENTH)
			balance++;
		if (tokens->symbol == T_RPARENTH)
			balance--;
		tokens = tokens->next;
	}
	if (balance != 0)
		return (0); // syntax error
	return (1);
}

t_container	*parse_prompt(t_tokens *tokens)
{
	t_container	*ctn;

	if (!parenth_check(tokens))
		return (NULL);
	ctn = ft_ctnnew(NULL, NULL);
	if (!ctn)
		return (NULL);
	parse_logex(ctn, tokens);
}

t_container	*parse_logex(t_container *ctn, t_tokens *tokens)
{
	t_container	*next_ctn;

	next_ctn = NULL;
	parse_pipeline(ctn, tokens);
	if (tokens && (tokens->symbol == T_AND || tokens->symbol == T_OR))
	{
		if (tokens->symbol == T_AND)
			ctn->operator= T_AND;
		else
			ctn->operator== T_OR;
		ft_tokpop(tokens);
		next_ctn = ft_ctnnew(NULL, NULL);
		if (!next_ctn)
			return (NULL); // needs free function
		ctn->type = T_CTN;
		ctn->next_ctn = parse_logex(next_ctn, tokens);
		return (next_ctn);
	}
	return (ctn);
}

t_container	*parse_pipeline(t_container *ctn, t_tokens *tokens)
{
	t_command	next_cmd;

	next_cmd = NULL;
	ctn->cmd = parse_command(ctn, tokens);
	if (tokens && tokens->symbol == T_PIPE)
	{
	}
}

// t_cmd ?? replace by t_ctn or split function, needs to be studied
t_command	parse_command(t_container *ctn, t_tokens *tokens)
{
	t_command	cmd;
	t_tokens	*last;

	// check for brace group && call parse cmd again
	cmd.args = tokens;
	while (tokens && tokens->symbol == T_ARG)
		ft_tokpop(tokens);
	last = ft_toklast(cmd.args);
	last->next = NULL;
	parse_redlist(ctn, tokens);
	return (cmd);
}

int	parse_redlist(t_container *ctn, t_tokens *tokens)
{
	e_symbol symbol;

	if (is_symbol_set(4, 0, tokens->symbol, T_APPEND, T_HEREDOC, T_INPUT,
			T_OUTPUT))
	{
		symbol = tokens->symbol;
		ft_tokpop(tokens);
		if (tokens->symbol != T_ARG)
			return (0); // syntax error unexpected token
		ft_tokadd_back(&ctn->redirects, tokens->symbol);
		ft_tokpop(tokens);
		parse_redlist(ctn, tokens);
	}
	return (1);
}