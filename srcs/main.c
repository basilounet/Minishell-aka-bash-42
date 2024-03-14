/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangouil <gangouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:22:02 by gangouil          #+#    #+#             */
/*   Updated: 2024/03/11 17:32:56 by gangouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <lexer.h>

static void	print_tokens(t_tokens *tokens)
{
	while (tokens)
	{
		printf("symbol = %u, arg = %s\n", tokens->symbol, tokens->arg);
		tokens = tokens->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_tokens	*tokens;

	(void)argc;
	(void)argv;
	(void)envp;
	tokens = NULL;
	while (1)
	{
		line = readline(NULL);
		if (lexer(&tokens, line) == 0)
			write(2, "invalid prompt\n", 15);
		print_tokens(tokens);
		parse_prompt(tokens);
		//write(1, line, sizeof(line));
		free(line);
		ft_tokclear(tokens);
		line = NULL;
		tokens = NULL;
	}
}
