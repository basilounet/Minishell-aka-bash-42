/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:50:58 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/15 21:13:07 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_cmd(t_execution execution, t_node *node)
{
	int	pid;

	expand_args(execution.ms, node);
	if (!execution.is_in_pipe && node->cmd.args && is_built_in(node->cmd.args->arg))
	{
		execute_built_ins(execution, node);
		parent(execution);
		return ;
	}
	execution.ms->pids = add_pid_space(execution.ms, execution.ms->pids);
	pid = fork();
	execution.ms->pids[pids_len(execution.ms->pids) - 1] = pid;
	if (pid < 0)
		execution.ms->exit_code = perr(1, 1, 1, strerror(errno));
	if (pid == 0)
		child(execution, node);
	parent(execution);
}


void	execute_node(t_execution execution, t_node *node, t_symbol last_operator)
{
	if (expand_redirects(execution.ms, node))
		return ;
	update_inputs(node);
	update_outputs(node);
	if (node->type == T_TREE)
	{
		if (node->tree.operator == T_PIPE)
		{
			if (pipe(execution.right_pipe) == -1)
				execution.ms->exit_code = perr(1, 1, 1, strerror(errno));
			execution.is_in_pipe = 1;
		}
		if (execution.is_in_pipe && last_operator == T_PIPE && node->tree.operator != T_PIPE)
		{
			execution.upper_pipe[0] = execution.right_pipe[0];
			execution.upper_pipe[1] = execution.right_pipe[1];
			execution.right_pipe[0] = -1;
			execution.right_pipe[1] = -1;
			execution.lower_pipe[0] = execution.left_pipe[0];
			execution.lower_pipe[1] = execution.left_pipe[1];
			execution.left_pipe[0] = -1;
			execution.left_pipe[1] = -1;
		}
		execute_node(execution, node->tree.left, node->tree.operator);
		if (node->tree.operator == T_PIPE)
		{
			try_close_fd(execution.right_pipe[WRITE]);
			execution.left_pipe[0] = execution.right_pipe[0];
			execution.left_pipe[1] = execution.right_pipe[1];
			execution.right_pipe[0] = -1;
			execution.right_pipe[1] = -1;
		}
		if (node->tree.operator != T_PIPE)
			wait_pids(execution.ms);
		if (node->tree.operator == T_PIPE || (node->tree.operator == T_AND
				&& execution.ms->exit_code == 0) || (node->tree.operator == T_OR
				&& execution.ms->exit_code != 0))
			execute_node(execution, node->tree.right, node->tree.operator);
		parent(execution);
	}
	else
		execute_cmd(execution, node);
}

/*
(export A=blip < c && cat) < $A
(sleep 1 | cat a && sleep 1 | cat b && sleep 1 | cat c) | cat -e
(cat a && cat b) | cat -e
*/