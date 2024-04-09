/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:50:58 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/09 17:24:56 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_cmd(t_execution execution, t_node *node)
{
	int	pid;

	execution.ms->exit_code = 0;
	expand_args(execution.ms, node);
	expand_redirects(execution.ms, node);
	execution.input = get_input_fd(execution.ms, node->cmd.redirects);
	execution.output = get_output_fd(node->cmd.redirects);
	if (node->cmd.args)
		check_command(execution.ms, &node->cmd.args->arg);
	transform_to_chars(node);
	// ft_print_map(node->cmd.char_args);
	if (execution.ms->exit_code != 0 || !node->cmd.args)
		return ;
	if (execution.is_in_pipe || !(is_built_in(node->cmd.args->arg)
			&& execute_built_ins(execution, node)))
	{
		execution.ms->pids = add_pid_space(execution.ms, execution.ms->pids);
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
		//print_pid(execution.ms->pids);
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
