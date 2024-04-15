/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:14:40 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/15 21:27:13 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <builts_in.h>

void	transform_to_chars(t_ms *ms, t_node *node)
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
		{
			ms->exit_code = 1;
			return ;
		}
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
		tmp_tok->arg = expand_var(ms->env, tmp_char, (t_expand_args){0, 1, 1, 1});
		if (tmp_tok->arg[0] == 0)
		{
			shift_tokens(&tmp_tok);
			free(tmp_char);
			continue ;
		}
		if (should_split_ifs(tmp_char))
			split_ifs(&tmp_tok);
		free(tmp_char);
		if (tmp_tok)
			tmp_tok = tmp_tok->next;
	}
}

int	expand_redirects(t_ms *ms, t_node *node)
{
	t_tokens	*tmp_tok;
	char		*tmp_char;

	if (node->type == T_TREE)
		tmp_tok = node->tree.redirects;
	else
		tmp_tok = node->cmd.redirects;
	while (tmp_tok)
	{
		if (T_OUTPUT <= tmp_tok->symbol && tmp_tok->symbol <= T_INPUT)
		{
			tmp_char = tmp_tok->arg;
			tmp_tok->arg = expand_var(ms->env, tmp_char, (t_expand_args){0, 1, 1, 1});
			if ((should_split_ifs(tmp_char) && ft_countc(tmp_tok->arg, -1)) || tmp_tok->arg[0] == 0)
			{
				free(tmp_char);
				ms->exit_code = perr(1, 1, 1, "ambiguous redirect\n");
				return (1);
			}
			ft_free_ptr(1, tmp_char);
			if (check_input(ms, tmp_tok))
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
	ms->exit_code = perr(127, 2, 1, *cmd, " : command not found");
}

void	reset_envp(t_ms *ms)
{
	if (ms->envp)
		ft_free_map(ms->envp, ft_maplen(ms->envp));
	ms->envp = ft_split(ft_getenv(ms->env, "PATH"), ':');
	if (!ms->envp)
		ms->exit_code = 1;
	if (ms->char_env)
		ft_free_map(ms->char_env, ft_maplen(ms->char_env));
	ms->char_env = env_list_to_array(ms->env);
	if (!ms->char_env)
		ms->exit_code = 1;
}

void	prepare_and_execute(t_ms *ms, t_node *node)
{
	ms->root_node = node;
	ms->exit_code = 0;
	reset_envp(ms);
	//print_node(node, 0);
	execute_node((t_execution){ms, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, -1, -1, 0}, node, 0);
	wait_pids(ms);
	unlink_here_docs(ms);
	ms->root_node = NULL;
}
