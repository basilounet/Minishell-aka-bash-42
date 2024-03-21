/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:22:02 by gangouil          #+#    #+#             */
/*   Updated: 2024/03/17 14:14:00 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
	t_node		*node;

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
		node = parse_prompt(tokens);
		//print_ctns(ctn, 1);
		// write(1, line, sizeof(line));
		free(line);
		//ft_tokclear(tokens);
		line = NULL;
		tokens = NULL;
	}
}