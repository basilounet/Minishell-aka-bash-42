/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 02:50:01 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/24 15:30:53 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	start_built_ins(t_execution execution, t_node *node)
{
	if (!ft_strcmp(node->cmd.args->arg, "echo"))
		echo(execution.ms, node->cmd.char_args);
	else if (!ft_strcmp(node->cmd.args->arg, "exit"))
		execution.ms->should_exit = ft_exit(execution.ms, node->cmd.char_args, \
		execution.is_in_pipe);
	else if (!ft_strcmp(node->cmd.args->arg, "cd"))
		cd(execution.ms, &execution.ms->env, node->cmd.char_args);
	else if (!ft_strcmp(node->cmd.args->arg, "pwd"))
		pwd(execution.ms);
	else if (!ft_strcmp(node->cmd.args->arg, "export"))
	{
		export(execution.ms, &execution.ms->env, node->cmd.char_args);
		reset_envp(execution.ms);
	}
	else if (!ft_strcmp(node->cmd.args->arg, "unset"))
	{
		unset(execution.ms, &execution.ms->env, node->cmd.char_args);
		reset_envp(execution.ms);
	}
	else if (!ft_strcmp(node->cmd.args->arg, "env"))
		env(execution.ms, execution.ms->env, node->cmd.char_args);
	else
		return (0);
	return (1);
}

int	execute_built_ins(t_execution execution, t_node *node)
{
	int	std_out;

	if (!execution.is_in_pipe)
	{
		execution.input = get_input_fd(node->cmd.redirects);
		execution.output = get_output_fd(node->cmd.redirects);
		if (node->cmd.args)
			check_command(execution.ms, &node->cmd.args->arg);
		transform_to_chars(execution.ms, node);
		std_out = dup(STDOUT_FILENO);
		if (execution.output >= 0)
			dup2(execution.output, STDOUT_FILENO);
	}
	start_built_ins(execution, node);
	if (execution.is_in_pipe)
	{
		ft_free_ms(execution.ms);
		exit(execution.ms->exit_code);
	}
	dup2(std_out, STDOUT_FILENO);
	try_close_fd(execution.input);
	try_close_fd(execution.output);
	close(std_out);
	return (1);
}

static void	dup_child(t_execution execution)
{
	if (execution.input >= 0)
		dup2(execution.input, STDIN_FILENO);
	else if (execution.left_pipe[READ] >= 0)
		dup2(execution.left_pipe[READ], STDIN_FILENO);
	else if (execution.lower_pipe[READ] >= 0)
		dup2(execution.lower_pipe[READ], STDIN_FILENO);
	if (execution.output >= 0)
		dup2(execution.output, STDOUT_FILENO);
	else if (execution.right_pipe[WRITE] >= 0)
		dup2(execution.right_pipe[WRITE], STDOUT_FILENO);
	else if (execution.upper_pipe[WRITE] >= 0)
		dup2(execution.upper_pipe[WRITE], STDOUT_FILENO);
}

void	child(t_execution execution, t_node *node)
{
	signal(SIGPIPE, SIG_IGN);
	set_interactive_mode(3);
	execution.input = get_input_fd(node->cmd.redirects);
	execution.output = get_output_fd(node->cmd.redirects);
	if (node->cmd.args)
		execution.ms->error_occured += check_command(execution.ms,
				&node->cmd.args->arg);
	execution.ms->error_occured += transform_to_chars(execution.ms, node);
	dup_child(execution);
	close_all_fds();
	if (execution.should_execute && node->cmd.args
		&& !execution.ms->error_occured && !(is_built_in(node->cmd.args->arg)
			&& execute_built_ins(execution, node)))
		execve(node->cmd.char_args[0], node->cmd.char_args,
			execution.ms->char_env);
	ft_free_ms(execution.ms);
	exit(execution.ms->exit_code);
}

void	parent(t_execution execution)
{
	try_close_fd(execution.input);
	try_close_fd(execution.output);
	try_close_fd(execution.right_pipe[WRITE]);
	try_close_fd(execution.left_pipe[READ]);
}
