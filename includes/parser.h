/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:41:56 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/02 10:06:49 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <lexer.h>
# include <libft.h>
# include <stdio.h>
/*
 * Container type
 */
typedef enum e_type
{
	T_CMD,
	T_TREE,
}						t_type;

typedef struct s_command
{
	t_tokens			*args;
	char				**char_args;
	t_tokens			*redirects;
}						t_command;

typedef struct s_node	t_node;

typedef struct s_binary_tree
{
	e_symbol			operator;
	t_node				*left;
	t_node				*right;
	t_tokens			*redirects;
}						t_tree;

typedef struct s_node
{
	t_type				type;
	union
	{
		t_command		cmd;
		t_tree			tree;
	};
	int	**pipes[2];
}						t_node;

int	parse_redlist(t_node *node, t_tokens **tokens);
char	*symbol_to_char(t_tokens *token);
int						is_symbol_set(int n, int exclude, e_symbol compared, ...);
int						parenth_check(t_tokens *tokens);
t_node					*ft_treenew(e_symbol ope, t_node *left, t_node *right, t_tokens *redirs);
t_node					*ft_nodenew(t_type type, t_command cmd, t_tree tree);
t_command				ft_cmdnew(t_tokens *args, t_tokens *redirects);
void					free_node(t_node *node);
t_node					*parse_prompt(t_tokens **tokens);
t_node					*parse_logex(t_tokens **tokens);
t_node					*parse_pipeline(t_tokens **tokens);
t_node					*parse_command(t_tokens **tokens);
t_node					*parse_brace(t_tokens **tokens);
t_node					*parse_simple_command(t_tokens **tokens);

#endif