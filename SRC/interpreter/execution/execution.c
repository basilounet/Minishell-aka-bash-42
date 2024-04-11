/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:50:58 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/11 15:31:59 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_cmd(t_execution execution, t_node *node)
{
	int	pid;

	execution.ms->exit_code = 0;
	expand_args(execution.ms, node);
	// ft_print_map(node->cmd.char_args);
	if (execution.ms->exit_code != 0)
	{
		parent(execution);
		return ;
	}
	if (execution.is_in_pipe || !(node->cmd.args && is_built_in(node->cmd.args->arg)
			&& execute_built_ins(execution, node)))
	{
		execution.ms->pids = add_pid_space(execution.ms, execution.ms->pids);
		pid = fork();
		//ft_printf("new_pid : %d\n", pid);
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
	expand_redirects(execution.ms, node);
	update_inputs(node);
	update_outputs(node);
	//print_node(execution.ms->root_node, 0);
	if (node->type == T_TREE)
	{
		if (node->tree.operator == T_PIPE)
			execution.is_in_pipe = 1;
		if (node->tree.operator == T_PIPE)
			pipe(execution.right_pipe);
		execute_node(execution, node->tree.left);
		if (node->tree.operator == T_PIPE)
		{
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
			execute_node(execution, node->tree.right);
	}
	else
		execute_cmd(execution, node);
}


/*
(export A=blip < c && cat) < $A
(sleep 1 | cat a && sleep 1 | cat b && sleep 1 | cat c) | cat -e
*/