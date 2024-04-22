/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:11:19 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/19 18:38:08 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_symbol(char *c, int i)
{
	if (c[i] == '|' && c[i + 1] == '|')
		return (T_OR);
	if (c[i] == '&' && c[i + 1] == '&')
		return (T_AND);
	if (c[i] == '>' && c[i + 1] == '>')
		return (T_APPEND);
	if (c[i] == '<' && c[i + 1] == '<')
		return (T_HEREDOC);
	if (c[i] == '|')
		return (T_PIPE);
	if (c[i] == '<')
		return (T_INPUT);
	if (c[i] == '>')
		return (T_OUTPUT);
	if (c[i] == '(')
		return (T_LPARENTH);
	if (c[i] == ')')
		return (T_RPARENTH);
	return (T_ARG);
}

static void	lex_string(t_ms *ms, t_tokens *tokens, char *line, int *i)
{
	int	dquoted;
	int	squoted;
	int	i_start;

	squoted = 0;
	dquoted = 0;
	i_start = *i;
	while (line[*i])
	{
		if (line[*i] == '\"' && squoted % 2 == 0)
			dquoted++;
		if (line[*i] == '\'' && dquoted % 2 == 0)
			squoted++;
		if (dquoted % 2 == 0 && squoted % 2 == 0 && (ft_isifs(line[*i])
				|| is_symbol(line, *i + 1) != T_ARG))
			break ;
		(*i)++;
	}
	if (squoted % 2 == 1 || dquoted % 2 == 1)
		tokens->arg = NULL;
	else
		tokens->arg = ft_substrc(line, i_start, *i + 1);
	if (!tokens->arg)
		perr((t_perr){ms, 1, 1, 1}, "unclosed quote");
}

int	lexer(t_ms *ms, t_tokens **tokens, char *line)
{
	int			i;
	t_tokens	*new_token;

	i = -1;
	while (line && line[++i])
	{
		while (ft_isifs(line[i]))
			i++;
		if (!line[i])
			return (1);
		new_token = ft_toknew(is_symbol(line, i), NULL, NULL);
		if (!new_token)
			return (0);
		if (new_token->symbol == T_ARG)
			lex_string(ms, new_token, line, &i);
		ft_tokadd_back(tokens, new_token);
		if (new_token->symbol == T_ARG && new_token->arg == NULL)
			return (0);
		if (!line[i])
			return (1);
		if (new_token->symbol == T_OR || new_token->symbol == T_AND
			|| new_token->symbol == T_APPEND || new_token->symbol == T_HEREDOC)
			i++;
	}
	return (1);
}
