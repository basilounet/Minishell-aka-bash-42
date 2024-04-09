/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:50:58 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/09 10:16:34 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_cmd(t_execution execution, t_node *node)
{
	int	pid;

	expand_args(execution.ms, node);
	expand_redirects(execution.ms, node);
	execution.input = get_input_fd(execution.ms, node->cmd.redirects);
	execution.output = get_output_fd(node->cmd.redirects);
	if (node->cmd.args)
		check_command(execution.ms, &node->cmd.args->arg);
	transform_to_chars(node);
	// ft_print_map(node->cmd.char_args);
	if (g_exitcode != 0 || !node->cmd.args)
		return ;
	if (execution.is_in_pipe || !(is_built_in(node->cmd.args->arg)
			&& execute_built_ins(execution, node)))
	{
		execution.ms->pids = add_pid_space(execution.ms->pids);
		pid = fork();
		execution.ms->pids[pids_len(execution.ms->pids) - 1] = pid;
		if (pid < 0)
			ft_printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa FORK BOMB\n");
		if (pid == 0)
			child(execution, node);
	}
	parent(execution);
}

void	execute_node(t_execution execution, t_node *node)
{
	int	i;
	
	if (node->type == T_TREE)
	{
		if (node->tree.operator == T_PIPE)
			execution.is_in_pipe = 1;
		if (node->tree.operator == T_PIPE)
			pipe(execution.right_pipe);
		execute_node(execution, node->tree.left);
		if (node->tree.operator == T_PIPE)
		{
			execution.left_pipe[READ] = execution.right_pipe[READ];
			execution.left_pipe[WRITE] = execution.right_pipe[WRITE];
			execution.right_pipe[READ] = -1;
			execution.right_pipe[WRITE] = -1;
		}
		print_pid(execution.ms->pids);
		if (node->tree.operator != T_PIPE && execution.ms->pids)
		{
			i = 0;
			while (execution.ms->pids[i] != -1)
				waitpid(execution.ms->pids[i++], NULL, 0);
			free(execution.ms->pids);
			execution.ms->pids = NULL;
		}
		execute_node(execution, node->tree.right);
	}
	else
		execute_cmd(execution, node);
}
