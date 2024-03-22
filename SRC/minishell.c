/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:47:49 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/22 16:38:29 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parser.h>

static void	print_tokens(t_tokens *tokens)
{
	while (tokens)
	{
		printf("symbol = %u, arg = \"%s\"\n", tokens->symbol, tokens->arg);
		tokens = tokens->next;
	}
}

int	main(int ac, char **av, char **env)
{
	t_ms		ms;
	char		*line;
	t_tokens	*tokens;
	t_node		*node;

	(void)ac;
	(void)av;
	tokens = NULL;
	ms.env = ft_mapcpy(env, ft_maplen(env));
	ms.prompt = add_colors(get_prompt(&ms), &moving_rainbow_pattern);
	while (1)
	{
		line = readline(ms.prompt);
		add_history(line);
		if (lexer(&tokens, line) == 0)
		{
			write(2, "invalid prompt\n", 15);
			ft_tokclear(tokens);
		}
		if (!tokens)
			write(2, "empty\n", 6);
		print_tokens(tokens);
		node = parse_prompt(&tokens);
		if (node)
			write(1, "good\n", 5);
		execute_all_commands(&ms, node);
		if (line)
			free(line);
		free(ms.prompt);
		ms.prompt = add_colors(get_prompt(&ms), &moving_rainbow_pattern);
	}
	free(ms.prompt);
	ft_free_map(ms.env, ft_maplen(ms.env));
}
