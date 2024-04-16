/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 13:59:12 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/15 13:47:54 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	has_input(t_tokens *tokens)
{
	t_tokens	*tmp;

	tmp = tokens;
	while (tmp && tmp->symbol != T_INPUT && tmp->symbol != T_HEREDOC)
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
		if (tmp->symbol == T_FINAL_INPUT || tmp->symbol == T_FINAL_HEREDOC)
			last_input = tmp;
		tmp = tmp->next;
	}
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
		if (tmp->symbol == T_FINAL_OUTPUT || tmp->symbol == T_FINAL_APPEND)
			last_output = tmp;
		tmp = tmp->next;
	}
	return (last_output);
}

int	get_input_fd(t_tokens *tokens)
{
	tokens = get_input_tok(tokens);
	if (!tokens)
		return (-1);
	return (open(tokens->arg, O_RDONLY));
}

int	get_output_fd(t_tokens *tokens)
{
	tokens = get_output_tok(tokens);
	if (!tokens)
		return (-1);
	if (tokens->symbol == T_FINAL_OUTPUT)
		return (open(tokens->arg, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	if (tokens->symbol == T_FINAL_APPEND)
		return (open(tokens->arg, O_CREAT | O_WRONLY | O_APPEND, 0777));
	return (-1);
}
