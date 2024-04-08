/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:47:49 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/08 14:38:49 by bvasseur         ###   ########.fr       */
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


/*static char *test[] = {"bla =bli", "bloups", "blagz=", \
	" ", "\"blarbouste\"", "zg\"oug", "bi\"z\"bou", "bi\"z'\"baz", \
	"blax='", "blax=''", "bist=ouri", "bist==ouri", "blorgux=test", \
	"bi\"s\"carosse", "", "bip=", "biap=titou", "bop=\"\"", "bap", \
	"miaousse=\'\"\'$USER\'\"\'", "_zblox=b", "1two3=", "one23=", \
	"b_3=", "bip=swag", "A=\"guy2bezbar\"", "A", "bix=", "bix+=bloarg", \
	"biop", "biop+=$bip", "moufette", NULL};
static char *test2[] = {"export", NULL};
static char *test3[] = {"c*", "*", "t*", "*a*", "*ak*", "**", "*s", \
	"*cases", "cases*", "cas*es", "case*s", "c*ases", NULL};*/

static void	temp_execution(t_ms *ms, char *line)
{
	t_tokens	*tokens;
	t_node		*node;

	tokens = NULL;
	if (lexer(&tokens, line) == 0)
	{
		ft_tokclear(&tokens);
		free(line);
		return ; //malloc error
	}
	node = parse_prompt(&tokens);
	if (!node)
	{
		free(line);
		return ;
	}
	prepare_and_execute(ms, node);
	free_node(node);
	ft_tokclear(&tokens);
	if (line)
		free(line);
	return ;
}

int	g_exitcode;

int	main(int ac, char **av, char **char_env)
{
	t_ms		ms;
	char		*line;

	(void)ac;
	(void)av;
	ft_memset((void *)&ms, 0, sizeof(t_ms));
	if (env_array_to_list(&(ms.env), char_env) == 0)
		return (1);
	ms.prompt = add_colors(get_prompt(ms.env), &moving_rainbow_pattern);
	while (1)
	{
		line = readline(ms.prompt);
		if (!line)
			break ;
		if (g_exitcode != -2147483647)
		{
			add_history(line);
			temp_execution(&ms, line);
		}
		free(ms.prompt);
		ms.prompt = add_colors(get_prompt(ms.env), &moving_rainbow_pattern);
	}
	rl_clear_history();
	free(ms.prompt);
	ft_envclear(ms.env);
}
