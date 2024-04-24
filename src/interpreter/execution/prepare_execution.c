/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:14:40 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/24 15:04:52 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builts_in.h>
#include <minishell.h>

int	transform_to_chars(t_ms *ms, t_node *node)
{
	t_tokens	*tmp_tok;
	int			i;

	if (node->type == T_TREE)
		return (0);
	else
	{
		i = 0;
		tmp_tok = node->cmd.args;
		node->cmd.char_args = ft_calloc(sizeof(char *),
				ft_toksize(node->cmd.args) + 1);
		if (!node->cmd.char_args)
		{
			perr((t_perr){ms, 1, 1, 1}, "A malloc error occured");
			return (1);
		}
		while (tmp_tok)
		{
			node->cmd.char_args[i++] = tmp_tok->arg;
			tmp_tok = tmp_tok->next;
		}
	}
	return (0);
}

int	check_directory(t_ms *ms, char *cmd)
{
	if (ft_countc(cmd, '/'))
	{
		if (is_existing_dir(cmd))
		{
			perr((t_perr){ms, 126, 2, 1}, cmd, ": Is a directory");
			return (1);
		}
		else
			access(cmd, X_OK);
		if (errno == EACCES)
			perr((t_perr){ms, 126, 3, 1}, cmd, ": ", strerror(errno));
		else
			perr((t_perr){ms, 127, 3, 1}, cmd, ": ", strerror(errno));
		return (1);
	}
	return (0);
}

int	check_command(t_ms *ms, char **cmd)
{
	char	*str;
	int		i;

	if (is_built_in(*cmd) || (!is_existing_dir(*cmd)
			&& !access(*cmd, F_OK) && !access(*cmd, X_OK)))
		return (0);
	i = -1;
	while (cmd && *cmd && *cmd[0] && ms->envp && ms->envp[++i])
	{
		str = ft_strjoin3(ms->envp[i], "/", *cmd);
		if (!str)
			return (1);
		if (!access(str, F_OK) && !access(str, X_OK))
		{
			free(*cmd);
			*cmd = str;
			return (0);
		}
		free(str);
	}
	if (check_directory(ms, *cmd))
		return (1);
	perr((t_perr){ms, 127, 2, 1}, *cmd, " : command not found");
	return (1);
}

int	reset_envp(t_ms *ms)
{
	if (ms->envp)
		ft_free_map(ms->envp, ft_maplen(ms->envp));
	ms->envp = ft_split(ft_getenv(ms->env, "PATH"), ':');
	if (ms->char_env)
		ft_free_map(ms->char_env, ft_maplen(ms->char_env));
	ms->char_env = env_list_to_array(ms->env);
	if (!ms->char_env)
	{
		perr((t_perr){ms, 1, 1, 1}, "A malloc error occurred");
		return (1);
	}
	return (0);
}

void	prepare_and_execute(t_ms *ms, t_node *node)
{
	set_interactive_mode(2);
	ms->error_occured = 0;
	ms->error_occured = reset_envp(ms);
	if (DEBUG)
		print_node(node, 0);
	if (ms->error_occured || g_sig == SIGINT)
	{
		unlink_here_docs(ms);
		return ;
	}
	ms->root_node = node;
	ms->tokens = NULL;
	execute_node((t_execution){ms, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, -1,
		-1, 0, 1}, node, 0);
	wait_pids(ms);
	if (DEBUG)
		ft_printf("exit_code : %d\n", ms->exit_code);
	unlink_here_docs(ms);
	g_sig = 0;
	ms->error_occured = 0;
	ms->root_node = NULL;
}
