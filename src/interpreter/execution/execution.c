/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:50:58 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/23 18:43:14 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	swap_fd(int left_fd[2], int right_fd[2])
{
	left_fd[0] = right_fd[0];
	left_fd[1] = right_fd[1];
	right_fd[0] = -1;
	right_fd[1] = -1;
}

static t_execution	execute_left(t_execution execution, t_node *node,
		t_symbol last_operator)
{
	if (node->tree.operator == T_PIPE)
	{
		if (pipe(execution.right_pipe) == -1)
			perr((t_perr){execution.ms, 1, 1, 1}, strerror(errno));
		execution.is_in_pipe = 1;
	}
	if (execution.is_in_pipe && last_operator == T_PIPE
		&& node->tree.operator != T_PIPE)
	{
		swap_fd(execution.upper_pipe, execution.right_pipe);
		swap_fd(execution.lower_pipe, execution.left_pipe);
	}
	execute_node(execution, node->tree.left, node->tree.operator);
	return (execution);
}

static t_execution	execute_right(t_execution execution, t_node *node,
		t_symbol last_operator)
{
	(void)last_operator;
	if (node->tree.operator == T_PIPE)
	{
		try_close_fd(execution.right_pipe[WRITE]);
		swap_fd(execution.left_pipe, execution.right_pipe);
	}
	if (node->tree.operator != T_PIPE)
		wait_pids(execution.ms);
	if (node->tree.operator == T_PIPE || (node->tree.operator == T_AND
			&& execution.ms->exit_code == 0) || (node->tree.operator == T_OR
			&& execution.ms->exit_code != 0))
		execute_node(execution, node->tree.right, node->tree.operator);
	parent(execution);
	return (execution);
}

static void	execute_cmd(t_execution execution, t_node *node)
{
	int	pid;

	if (g_sig == SIGINT)
	{
		execution.ms->exit_code = 130;
		return ;
	}
	if (expand_args(execution.ms, node, node->cmd.args && \
	!ft_strcmp(node->cmd.args->arg, "export")) && !execution.ms->error_occured)
		execution.ms->exit_code = 0;
	if (!execution.is_in_pipe && node->cmd.args && !execution.ms->error_occured
		&& is_built_in(node->cmd.args->arg))
	{
		execute_built_ins(execution, node);
		parent(execution);
		return ;
	}
	execution.ms->pids = add_pid_space(execution.ms, execution.ms->pids);
	pid = fork();
	execution.ms->pids[pids_len(execution.ms->pids) - 1] = pid;
	if (pid < 0)
		perr((t_perr){execution.ms, 1, 1, 1}, strerror(errno));
	if (pid == 0)
		child(execution, node);
	parent(execution);
}

void	execute_node(t_execution execution, t_node *node,
		t_symbol last_operator)
{
	if (execution.should_execute)
		execution.ms->error_occured = 0;
	execution.ms->error_occured += expand_redirects(execution.ms, node);
	if (execution.ms->error_occured)
		execution.should_execute = 0;
	update_inputs(node);
	update_outputs(node);
	if (node->type == T_TREE)
	{
		execution = execute_left(execution, node, last_operator);
		execution = execute_right(execution, node, last_operator);
	}
	else
		execute_cmd(execution, node);
}
