/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:18:11 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/19 18:38:44 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*symbol_to_char(t_tokens *token)
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

int	is_symbol_set(int n, int exclude, t_symbol compared, ...)
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

int	parenth_check(t_ms *ms, t_tokens *tokens)
{
	int	balance;

	balance = 0;
	while (tokens)
	{
		if (balance < 0)
			break ;
		if (tokens->symbol == T_LPARENTH)
			balance++;
		if (tokens->symbol == T_RPARENTH)
			balance--;
		tokens = tokens->next;
	}
	if (balance > 0 || balance < 0)
	{
		if (balance > 0)
			perr((t_perr){ms, 2, 2, 1}, SYN_ERR, "`('");
		if (balance < 0)
			perr((t_perr){ms, 2, 2, 1}, SYN_ERR, "`)'");
		return (0);
	}
	return (1);
}
