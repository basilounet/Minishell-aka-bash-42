/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:32:18 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/24 15:30:00 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_expand	exp_args_core(t_ms *ms, t_node *node, t_tokens **tmp_tok,
		bool is_export)
{
	t_expand	exp_var;
	char		*tmp_char;

	tmp_char = (*tmp_tok)->arg;
	ft_memset(&exp_var, 0, sizeof(t_expand));
	if ((*tmp_tok)->symbol == T_ARG)
	{
		if (!is_export)
			exp_var = expand_var(ms, tmp_char, (t_expand_args){0, 1, 1, 1, 1});
		else
			exp_var = expand_var(ms, tmp_char, (t_expand_args){0, 1, 1, 0, 0});
		(*tmp_tok)->arg = exp_var.line;
		if (exp_var.is_expand)
			(*tmp_tok)->symbol = T_EXPAND;
	}
	else
		(*tmp_tok)->arg = ft_strdup(tmp_char);
	if ((*tmp_tok)->arg[0] == 0 && (*tmp_tok)->symbol == T_EXPAND && \
		!ft_countc(tmp_char, '"') && !ft_countc(tmp_char, '\''))
	{
		node->cmd.args = shift_tokens(node->cmd.args, tmp_tok);
		free(tmp_char);
		return ((t_expand){0});
	}
	return (exp_var);
}

int	expand_args(t_ms *ms, t_node *node, bool is_export)
{
	t_expand	exp_var;
	t_tokens	*tmp_tok;
	char		*tmp_char;

	tmp_tok = node->cmd.args;
	while (tmp_tok)
	{
		tmp_char = tmp_tok->arg;
		if (tmp_tok->symbol == T_ARG)
		{
			exp_var = exp_args_core(ms, node, &tmp_tok, is_export);
			if (!exp_var.line)
				continue ;
			if (should_split_ifs(tmp_char) || ft_countc(tmp_tok->arg, -1))
				split_ifs(&tmp_tok, exp_var.is_wildcard, exp_var.is_expand);
			free(tmp_char);
		}
		if (tmp_tok)
			tmp_tok = tmp_tok->next;
	}
	if (!node->cmd.args)
		return (1);
	return (0);
}

static int	exp_redirs_core(t_ms *ms, t_tokens *tmp_tok)
{
	t_expand	exp_var;
	char		*tmp_char;

	tmp_char = tmp_tok->arg;
	exp_var = expand_var(ms, tmp_char, (t_expand_args){0, 1, 1, 1, 1});
	tmp_tok->arg = exp_var.line;
	if (ft_countc(tmp_tok->arg, -1) || (tmp_tok->arg[0] == 0
			&& ft_countc(tmp_char, '$')))
	{
		perr((t_perr){ms, 1, 2, 1}, tmp_char, ": ambiguous redirect");
		free(tmp_char);
		return (0);
	}
	ft_free_ptr(1, tmp_char);
	if (check_input(ms, tmp_tok))
		return (0);
	return (1);
}

int	expand_redirects(t_ms *ms, t_node *node)
{
	t_tokens	*tmp_tok;

	if (node->type == T_TREE)
		tmp_tok = node->tree.redirects;
	else
		tmp_tok = node->cmd.redirects;
	while (tmp_tok)
	{
		if (T_OUTPUT <= tmp_tok->symbol && tmp_tok->symbol <= T_INPUT)
		{
			if (!exp_redirs_core(ms, tmp_tok))
				return (1);
		}
		else if (tmp_tok->symbol == T_HEREDOC)
			expand_here_doc(ms, tmp_tok);
		if (T_OUTPUT <= tmp_tok->symbol && tmp_tok->symbol <= T_HEREDOC)
			tmp_tok->symbol += 4;
		tmp_tok = tmp_tok->next;
	}
	return (0);
}
