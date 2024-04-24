/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:41:56 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/23 17:31:05 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <lexer.h>
# include <stdio.h>

# define SYN_ERR "syntax error near unexpected token "

typedef struct s_minishell	t_ms;

typedef enum e_type
{
	T_CMD,
	T_TREE,
}							t_type;

typedef struct s_command
{
	t_tokens				*args;
	char					**char_args;
	t_tokens				*redirects;
}							t_command;

typedef struct s_node		t_node;

typedef struct s_binary_tree
{
	t_symbol				operator;
	t_node					*left;
	t_node					*right;
	t_tokens				*redirects;
}							t_tree;

/*

*/
typedef struct s_node
{
	t_type					type;
	union
	{
		t_command			cmd;
		t_tree				tree;
	};
}							t_node;

/*========== LEXER ==========*/

int							lexer(t_ms *ms, t_tokens **tokens, char *line);
int							parenth_check(t_ms *ms, t_tokens *tokens);
char						*symbol_to_char(t_tokens *token);
int							is_symbol_set(int n, int exclude, t_symbol compared,
								...);

/*========== PARSER ==========*/

void						open_heredoc(t_ms *ms, char **stop);
int							parse_redlist(t_ms *ms, t_node *node,
								t_tokens **tokens);
t_node						*parse_prompt(t_ms *ms, t_tokens **tokens);
t_node						*parse_logex(t_ms *ms, t_tokens **tokens);
t_node						*parse_pipeline(t_ms *ms, t_tokens **tokens);
t_node						*parse_command(t_ms *ms, t_tokens **tokens);
t_node						*parse_brace(t_ms *ms, t_tokens **tokens);
t_node						*parse_simple_command(t_ms *ms, t_tokens **tokens);

/*========== NODES ==========*/

t_node						*ft_treenew(t_symbol ope, t_node *left,
								t_node *right, t_tokens *redirs);
t_node						*ft_nodenew(t_type type, t_command cmd,
								t_tree tree);
t_command					ft_cmdnew(t_tokens *args, t_tokens *redirects);
t_node						*free_node(t_node *node);

#endif