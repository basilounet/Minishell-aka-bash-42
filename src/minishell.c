/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:47:49 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/27 15:23:17 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builts_in.h>
#include <minishell.h>

int			g_sig;

void	ft_free_ms(t_ms *ms)
{
	ft_free_ptr(1, ms->prompt);
	ft_envclear(ms->env);
	ft_free_map(ms->envp, ft_maplen(ms->envp));
	ft_free_map(ms->char_env, ft_maplen(ms->char_env));
	free_node(ms->root_node);
	if (ms->pids)
		free(ms->pids);
}

static void	set_ms(t_ms *ms)
{
	if (g_sig == SIGINT)
		ms->exit_code = 130;
	ms->tokens = NULL;
	ms->heredoc_number = 0;
	ms->error_occured = 0;
}

static void	start_execution(t_ms *ms, char *line)
{
	t_node	*node;

	g_sig = 0;
	if (lexer(ms, &ms->tokens, line) == 0)
	{
		ft_tokclear(&ms->tokens);
		free(line);
		return ;
	}
	ft_free_ptr(1, line);
	if (!ms->tokens)
		return ;
	node = parse_prompt(ms, &ms->tokens);
	if (!node)
	{
		ft_tokclear(&ms->tokens);
		return ;
	}
	prepare_and_execute(ms, node);
	node = free_node(node);
	ft_tokclear(&ms->tokens);
	return ;
}

static void	minishell_loop(t_ms *ms)
{
	while (1)
	{
		ms->prompt = add_colors(get_prompt(ms->env), &moving_rainbow_pattern);
		set_interactive_mode(1);
		if (ms->should_exit)
			break ;
		ms->line = readline(ms->prompt);
		set_ms(ms);
		if (!ms->line)
			break ;
		if (ms->line[0] != '\0')
			add_history(ms->line);
		start_execution(ms, ms->line);
		ft_free_ptr(1, ms->prompt);
	}
}

int	main(int ac, char **av, char **char_env)
{
	t_ms	ms;

	(void)ac;
	(void)av;
	ft_memset((void *)&ms, 0, sizeof(t_ms));
	if (env_array_to_list(&(ms.env), char_env) == 0)
		return (1);
	minishell_loop(&ms);
	ft_putstr_fd("exit\n", 2);
	rl_clear_history();
	ft_free_ms(&ms);
	return (ms.exit_code);
}
