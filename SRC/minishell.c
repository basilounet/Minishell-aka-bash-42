/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:47:49 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/24 18:06:21 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parser.h>

/*
int	main(int ac, char **av, char **original_env)
{
	t_tokens	*tokens;
	t_tokens	*env;
	int			i;

	(void)ac;
	i = 1;
	tokens = NULL;
	env = NULL;
	while (av[i])
	{
		ft_tokadd_back(&tokens, ft_toknew(0, NULL));
		ft_toklast(tokens)->arg = ft_strdup(av[i]);
		i++;
	}
	i = 0;
	while (original_env[i])
	{		
		ft_tokadd_back(&env, ft_toknew(0, NULL));
		ft_toklast(env)->arg = ft_strdup(original_env[i]);
		i++;
	}
	pipex(tokens, env, 0);
	ft_tokclear(tokens);
	ft_tokclear(env);
}
*/

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
		//if (!tokens)
		//	write(2, "empty\n", 6);
		node = parse_prompt(&tokens);
		//if (node)
		//	write(1, "good\n", 5);
		//execute_node(&ms, node);
		if (line)
			free(line);
		free(ms.prompt);
		ms.prompt = add_colors(get_prompt(&ms), &moving_rainbow_pattern);
	}
	free(ms.prompt);
	ft_free_map(ms.env, ft_maplen(ms.env));
}
