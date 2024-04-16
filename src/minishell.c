/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:47:49 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/16 14:03:15 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builts_in.h>
#include <minishell.h>
#include <parser.h>

void	ft_free_ms(t_ms *ms)
{
	ft_tokclear(&ms->tokens);
	ft_free_ptr(1, ms->prompt);
	ft_envclear(ms->env);
	ft_free_map(ms->envp, ft_maplen(ms->envp));
	ft_free_map(ms->char_env, ft_maplen(ms->char_env));
	if (ms->pids)
		free(ms->pids);
}

static void	temp_execution(t_ms *ms, char *line)
{
	t_node	*node;

	ms->tokens = NULL;
	ms->heredoc_number = 0;
	if (lexer(ms, &ms->tokens, line) == 0)
	{
		ft_tokclear(&ms->tokens);
		free(line);
		ms->exit_code = perr(1, 1, 1, "A malloc error occured");
		return ;
	}
	node = parse_prompt(ms, &ms->tokens);
	if (!node)
	{
		ft_tokclear(&ms->tokens);
		free(line);
		return ;
	}
	prepare_and_execute(ms, node);
	printf("exit code = %d\n", ms->exit_code);
	node = free_node(node);
	ft_tokclear(&ms->tokens);
	if (line)
		free(line);
	return ;
}

int			g_sig;

int	main(int ac, char **av, char **char_env)
{
	t_ms	ms;

	(void)ac;
	(void)av;
	ft_memset((void *)&ms, 0, sizeof(t_ms));
	if (env_array_to_list(&(ms.env), char_env) == 0)
		return (1);
	ms.prompt = add_colors(get_prompt(ms.env), &moving_rainbow_pattern);
	set_interactive_mode(1);
	while (1)
	{
		set_interactive_mode(1);
		ms.line = readline(ms.prompt);
		if (!ms.line)
			break ;
		if (ms.line[0] != '\0')
			add_history(ms.line);
		temp_execution(&ms, ms.line);
		free(ms.prompt);
		ms.prompt = add_colors(get_prompt(ms.env), &moving_rainbow_pattern);
	}
	rl_clear_history();
	ft_free_ms(&ms);
}
