/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:14:40 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/09 11:26:17 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	transform_to_chars(t_node *node)
{
	t_tokens	*tmp_tok;
	int			i;

	if (node->type == T_TREE)
		return ;
	else
	{
		i = 0;
		tmp_tok = node->cmd.args;
		node->cmd.char_args = ft_calloc(sizeof(char *),
				ft_toksize(node->cmd.args) + 1);
		if (!node->cmd.char_args)
			return ;
		while (tmp_tok)
		{
			node->cmd.char_args[i++] = tmp_tok->arg;
			tmp_tok = tmp_tok->next;
		}
	}
}

void	expand_args(t_ms *ms, t_node *node)
{
	t_tokens	*tmp_tok;
	char		*tmp_char;

	if (node->type == T_TREE)
		return ;
	tmp_tok = node->cmd.args;
	while (tmp_tok)
	{
		tmp_char = tmp_tok->arg;
		tmp_tok->arg = expand_var(ms->env, tmp_char, (t_expand_args){0, 1, 1});
		if (should_split_ifs(tmp_char))
			split_ifs(&tmp_tok);
		free(tmp_char);
		if (tmp_tok)
			tmp_tok = tmp_tok->next;
	}
}

void	expand_redirects(t_ms *ms, t_node *node)
{
	t_tokens	*tmp_tok;
	char		*tmp_char;

	if (node->type == T_TREE)
		tmp_tok = node->tree.redirects;
	else
		tmp_tok = node->cmd.redirects;
	while (tmp_tok)
	{
		if (tmp_tok->symbol != T_HEREDOC)
		{
			tmp_char = tmp_tok->arg;
			tmp_tok->arg = expand_var(ms->env, tmp_char, (t_expand_args){0, 1, 1});
			if (should_split_ifs(tmp_char) && ft_countc(tmp_tok->arg, -1))
			{
				ft_printf("baseshell: ambiguous redirect\n");
				free(tmp_char);
				ms->exit_code = 1;
				return ;
			}
			ft_free_ptr(1, tmp_char);
		}
		if (tmp_tok)
			tmp_tok = tmp_tok->next;
	}
}

void	check_command(t_ms *ms, char **cmd)
{
	char	*str;
	int		i;

	if (!cmd || !*cmd || is_built_in(*cmd) || (!access(*cmd, F_OK) && !access(*cmd, X_OK)))
		return ;
	i = -1;
	while (ms->envp[++i])
	{
		str = ft_strjoin3(ms->envp[i], "/", *cmd);
		if (!str)
			return ;
		if (!access(str, F_OK) && !access(str, X_OK))
		{
			free(*cmd);
			*cmd = str;
			return ;
		}
		free(str);
	}
	ft_printf("baseshell: %s : command not found\n", *cmd);
	ms->exit_code = 127;
}

void	reset_envp(t_ms *ms)
{
	if (ms->envp)
		ft_free_map(ms->envp, ft_maplen(ms->envp));
	ms->envp = ft_split(ft_getenv(ms->env, "PATH"), ':');
	if (!ms->envp)
		ms->exit_code = 1;
}

void	prepare_and_execute(t_ms *ms, t_node *node)
{
	ms->exit_code = 0;
	ms->heredoc_number = 0;
	ms->root_node = node;
	open_all_outputs(ms, node);
	update_inputs(node);
	update_outputs(node);
	reset_envp(ms);
	//print_node(node, 0);
	execute_node((t_execution){ms, {-1, -1}, {-1, -1}, -1, -1, 0}, node);
	wait_pids(ms);
	unlink_here_docs(ms);
}
