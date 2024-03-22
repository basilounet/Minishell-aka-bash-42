/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:22:02 by gangouil          #+#    #+#             */
/*   Updated: 2024/03/22 14:56:29 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char	*symbol_to_char(e_symbol symbol)
{
	if (symbol == T_PIPE)
		return ("|");
	if (symbol == T_INPUT)
		return ("<");
	if (symbol == T_HEREDOC)
		return ("<<");
	if (symbol == T_OUTPUT)
		return (">");
	if (symbol == T_APPEND)
		return (">>");
	if (symbol == T_LPARENTH)
		return ("(");
	if (symbol == T_RPARENTH)
		return (")");
	if (symbol == T_OR)
		return ("||");
	if (symbol == T_AND)
		return ("&&");
	return (NULL);
}

static void	print_pad(int depth)
{
	while (depth)
	{
		printf("|  ");
		depth--;
	}
}

static void	print_tokens(t_tokens *tokens, int depth)
{
	while (tokens)
	{
		print_pad(depth);
		printf("symbol = %u, arg = \"%s\"\n", tokens->symbol, tokens->arg);
		tokens = tokens->next;
	}
}

static void	print_node(t_node *node, int depth)
{
	if (node->type == T_CMD)
	{
		print_pad(depth);
		printf("<cmd>\n");
		depth++;
		print_pad(depth);
		printf("<args>\n");
		depth++;
		print_tokens(node->cmd.args, depth);
		print_pad(depth - 1);
		printf("<redirects>\n");
		print_tokens(node->cmd.redirects, depth);
	}
	if (node->type == T_TREE)
	{
		print_pad(depth);
		printf("<tree>\n");
		depth++;
		print_pad(depth);
		printf("operator = %s\n", symbol_to_char(node->tree.operator));
		if (node->tree.left)
			print_node(node->tree.left, depth + 1);
		if (node->tree.right)
			print_node(node->tree.right, depth + 1);
		print_pad(depth);
		printf("<redirects>\n");
		print_tokens(node->tree.redirects, depth);
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
		if (line && line[0])
			add_history(line);
		if (lexer(&tokens, line) == 0)
		{
			write(2, "invalid prompt\n", 15);
			ft_tokclear(tokens);
			return (1);
		}
		if (!tokens)
		{
			write(2, "empty\n", 6);
			return (1);
		}
		//print_tokens(tokens, 0);
		node = parse_prompt(&tokens);
		if (!node)
			write(1, "bad\n", 4);
		else
			print_node(node, 0);
		//print_ctns(ctn, 1);
		// write(1, line, sizeof(line));
		free(line);	
		line = NULL;
		free_node(node);
		ft_tokclear(tokens);
	}
}
