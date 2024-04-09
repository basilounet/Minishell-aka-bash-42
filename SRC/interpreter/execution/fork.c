/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 02:50:01 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/08 20:23:49 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	try_close_fd(int fd)
{
	if (fd > 2)
		close(fd);
}

int	execute_built_ins(t_execution execution, t_node *node)
{
	if (!ft_strcmp(node->cmd.args->arg, "echo"))
		echo(node->cmd.char_args);
	else if (!ft_strcmp(node->cmd.args->arg, "cd"))
		cd(&execution.ms->env, node->cmd.char_args);
	else if (!ft_strcmp(node->cmd.args->arg, "pwd"))
		pwd();
	else if (!ft_strcmp(node->cmd.args->arg, "export"))
	{
		export(&execution.ms->env, node->cmd.char_args);
		reset_envp(execution.ms);
	}
	else if (!ft_strcmp(node->cmd.args->arg, "unset"))
	{
		unset(&execution.ms->env, node->cmd.char_args);
		reset_envp(execution.ms);
	}
	else if (!ft_strcmp(node->cmd.args->arg, "env"))
		env(execution.ms->env);
	else
		return (0);
	if (execution.is_in_pipe)
		exit(0);
	return (1);
/////////////////////////////////////////////////////////////////////////////////
}

void	child(t_execution execution, t_node *node)
{
	if (execution.input >= 0)
		dup2(execution.input, STDIN_FILENO);
	else if (execution.left_pipe[READ] >= 0)
		dup2(execution.left_pipe[READ], STDIN_FILENO);
	if (execution.output >= 0)
		dup2(execution.output, STDOUT_FILENO);
	else if (execution.right_pipe[WRITE] >= 0)
		dup2(execution.right_pipe[WRITE], STDOUT_FILENO);
	try_close_fd(execution.input);
	try_close_fd(execution.output);
	try_close_fd(execution.left_pipe[READ]);
	try_close_fd(execution.left_pipe[WRITE]);
	try_close_fd(execution.right_pipe[READ]);
	try_close_fd(execution.right_pipe[WRITE]);
	if (!execute_built_ins(execution, node))
		execve(node->cmd.char_args[0], node->cmd.char_args, execution.ms->envp);
}

void	parent(t_execution execution)
{
	try_close_fd(execution.input);
	try_close_fd(execution.output);
}
