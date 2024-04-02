/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:47:49 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/02 17:07:05 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parser.h>
#include <builts_in.h>

char	*symbol_to_char(e_symbol symbol)
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

void	print_pad(int depth)
{
	while (depth)
	{
		printf("|  ");
		depth--;
	}
}

void	print_tokens(t_tokens *tokens, int depth)
{
	while (tokens)
	{
		print_pad(depth);
		printf("symbol = %u, arg = \"%s\"\n", tokens->symbol, tokens->arg);
		tokens = tokens->next;
	}
}

void	print_node(t_node *node, int depth)
{
	if (!node)
		return ;
	if (node->type == T_CMD)
	{
		print_pad(depth);
		printf("<cmd>\n");
		print_pad(++depth);
		printf("<args>\n");
		print_tokens(node->cmd.args, depth);
		print_pad(++depth - 1);
		printf("<redirects>\n");
		print_tokens(node->cmd.redirects, depth);
	}
	if (node->type == T_TREE)
	{
		print_pad(depth);
		printf("<tree>\n");
		print_pad(++depth);
		printf("operator = %s\n", symbol_to_char(node->tree.operator));
		print_node(node->tree.left, depth + 1);
		print_node(node->tree.right, depth + 1);
		print_pad(depth);
		printf("<redirects>\n");
		print_tokens(node->tree.redirects, depth);
	}
}

int	main(int ac, char **av, char **char_env)
{
	t_ms		ms;
	char		*line;
	t_tokens	*tokens;
	t_node		*node;
	char		**argumentatos;

	(void)ac;
	(void)av;
	tokens = NULL;
	ms.env = NULL;
	
	if (env_array_to_list(&(ms.env), char_env) == 0)
		return (1); //malloc error
	//print_env(env); //debug
	//export(&env, test2);
	//print_env(env); //debug
	ms.prompt = add_colors(get_prompt(ms.env), &moving_rainbow_pattern);
	//ft_envclear(env);
	while (1)
	{
		line = readline(ms.prompt);
		add_history(line);
		if (ft_strncmp(line, "exit", 4) == 0)
		{
			free(line);
			break ;
		}
		else if (ft_strncmp(line, "export", 6) == 0)
		{
			argumentatos = ft_split(line, ' ');
			export(&(ms.env), argumentatos);
			free(argumentatos);
		}
		else if (ft_strncmp(line, "unset", 5) == 0)
		{
			argumentatos = ft_split(line, ' ');
			unset(&(ms.env), argumentatos);
			free(argumentatos);
		}
		else if (ft_strncmp(line, "env", 3) == 0)
			print_env(ms.env);
		if (lexer(&tokens, line) == 0)
		{
			write(2, "invalid prompt\n", 15);
			ft_tokclear(&tokens);
			return (1);
		}
		node = parse_prompt(&tokens);
		prepare_and_execute(&ms, node);
		if (line)
			free(line);
		free_node(node);
		ft_tokclear(&tokens);
		free(ms.prompt);
		ms.prompt = add_colors(get_prompt(ms.env), &moving_rainbow_pattern);
	}
	free(ms.prompt);
	ft_envclear(ms.env);
}
