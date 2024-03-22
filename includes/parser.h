/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangouil <gangouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:41:56 by gangouil          #+#    #+#             */
/*   Updated: 2024/03/20 15:41:57 by gangouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <lexer.h>
# include <stdio.h>
# include <libft.h>
/*
 * Container type
 */
typedef enum e_type
{
	T_CMD,
	T_TREE,
}							e_type;

typedef struct s_command
{
	t_tokens				*args;
	t_tokens				*redirects;
}	t_command;

typedef struct s_node t_node;

typedef struct s_binary_tree
{
	e_symbol	operator;
	t_node		*left;
	t_node		*right;
	t_tokens	*redirects;
}	t_tree;

typedef struct s_node
{
	e_type	type;
	union
	{
		t_command	cmd;
		t_tree		tree;
	};
}	t_node;

t_node	*ft_treenew(e_symbol ope, t_node *left, t_node *right, t_tokens *redirs);
t_node	*ft_nodenew(e_type type, t_command cmd, t_tree tree);
t_command	ft_cmdnew(t_tokens *args, t_tokens *redirects);
void	free_node(t_node *node);
t_node	*parse_prompt(t_tokens **tokens);
t_node	*parse_logex(t_tokens **tokens);
t_node	*parse_pipeline(t_tokens **tokens);
t_node	*parse_command(t_tokens **tokens);
t_node	*parse_brace(t_tokens **tokens);
t_node	*parse_simple_command(t_tokens **tokens);
int		parse_redlist(t_node *node, t_tokens **tokens);

#endif