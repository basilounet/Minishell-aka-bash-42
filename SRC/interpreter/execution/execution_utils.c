/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 13:59:12 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/24 14:56:11 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parser.h>

int	has_input(t_tokens *tokens)
{
	t_tokens *tmp;

	tmp = tokens;
	while (tmp && tmp->symbol != T_INPUT && tmp->symbol != T_HEREDOC)
		tmp = tmp->next;
	if (tmp)
		return (1);
	return (0);
}

int	has_output(t_tokens *tokens)
{
	t_tokens *tmp;

	tmp = tokens;
	while (tmp && tmp->symbol != T_OUTPUT && tmp->symbol != T_APPEND)
		tmp = tmp->next;
	if (tmp)
		return (1);
	return (0);
}

t_tokens	*get_input_tok(t_tokens *tokens)
{
	t_tokens	*last_input;
	t_tokens	*tmp;

	tmp = tokens;
	last_input = NULL;
	while (tmp)
	{
		if (tmp->symbol == T_INPUT || tmp->symbol == T_HEREDOC)
			last_input = tmp;
		tmp = tmp->next;
	}
	if (!last_input)
		return (NULL);
	return (last_input);
}

t_tokens	*get_output_tok(t_tokens *tokens)
{
	t_tokens	*last_output;
	t_tokens	*tmp;

	tmp = tokens;
	last_output = NULL;
	while (tmp)
	{
		if (tmp->symbol == T_OUTPUT || tmp->symbol == T_APPEND)
			last_output = tmp;
		tmp = tmp->next;
	}
	if (!last_output)
		return (NULL);
	return (last_output);
}

int	is_append(t_command *cmd)
{
	t_tokens	*tmp;

	tmp = cmd->redirects;
	while (tmp && tmp->symbol != T_APPEND)
		tmp = tmp->next;
	if (tmp && tmp->symbol == T_APPEND)
		return (1);
	return (0);
}

