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
#include <builts_in.h>

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

static const char *test[] = {"bla =bli", "bloups", "blagz=", \
	" ", "\"blarbouste\"", "zg\"oug", "bi\"z\"bou", "bi\"z'\"baz", \
	"blax='", "blax=''", "bist=ouri", "bist==ouri", "blorgux=test", \
	"bi\"s\"carosse", "", "bip=", "biap=titou", "bop=\"\"", "bap", \
	"miaousse=\'\"\'$USER\'\"\'", "_zblox=b", "1two3=", "one23=", \
	"b_3=", "bip=swag", "A=\"guy2bezbar\"", "A", "bix=", "bix+=bloarg", \
	"biop", "biop+=$bip", "moufette", NULL};
static const char *test2[] = {"export", NULL};

int	main(int ac, char **av, char **char_env)
{
	t_ms		ms;
	char		*line;
	t_tokens	*tokens;
	t_node		*node;
	t_env		*env;
	char		**argumentatos;

	(void)ac;
	(void)av;
	tokens = NULL;
	env = NULL;

	if (env_array_to_list(&env, char_env) == 0)
		return (1); //malloc error
	//print_env(env); //debug
	export(&env, test);
	//export(&env, test2);
	//print_env(env); //debug
	ms.env = ft_mapcpy(char_env, ft_maplen(char_env));
	//as we'll never actually modify the environment variables,
	//maybe simply give the char_env var to ms.env instead of copying it?
	ms.prompt = add_colors(get_prompt(env), &moving_rainbow_pattern);
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
			export(&env, argumentatos);
			free(argumentatos);
		}
		else if (ft_strncmp(line, "unset", 5) == 0)
		{
			argumentatos = ft_split(line, ' ');
			unset(&env, argumentatos);
			free(argumentatos);
		}
		else if (ft_strncmp(line, "env", 3) == 0)
			print_env(env);
		if (lexer(&tokens, line) == 0)
		{
			write(2, "invalid prompt\n", 15);
			ft_tokclear(&tokens);
			return (1);
		}
		if (!tokens)
			write(2, "empty\n", 6);
		print_tokens(tokens, 0);
		node = parse_prompt(&tokens);
		if (!node)
			write(1, "bad\n", 4);
		else
			print_node(node, 0);
		//execute_all_commands(&ms, node);
		if (line)
			free(line);
		free_node(node);
		ft_tokclear(&tokens);
		free(ms.prompt);
		ms.prompt = add_colors(get_prompt(env), &moving_rainbow_pattern);
	}
	free(ms.prompt);
	ft_free_map(ms.env, ft_maplen(ms.env));
	ft_envclear(env);
}
