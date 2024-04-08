/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:50:58 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/08 14:44:06 by bvasseur         ###   ########.fr       */
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
	//ft_print_map(node->cmd.char_args);
	if (g_exitcode != 0 || !node->cmd.args)
		return ;
	pid = fork();
	if (pid < 0)
		ft_printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa FORK BOMB\n");
	if (pid == 0)
		child(execution, node);
	else
		parent(execution);
}

void	execute_node(t_execution execution, t_node *node)
{
	if (node->type == T_TREE)
	{
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
		execute_node(execution, node->tree.right);
	}
	else
        execute_cmd(execution, node);
}
