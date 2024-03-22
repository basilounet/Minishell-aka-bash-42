/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:18:25 by gangouil          #+#    #+#             */
/*   Updated: 2024/03/22 16:44:21 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <libft.h>
# include <stddef.h>

/*
 * Tokens types
 * T_ARG,		// 0 cat
 * T_PIPE,		// 1 |
 * T_INPUT,		// 2 <
 * T_HEREDOC,	// 3 <<
 * T_OUTPUT,	// 4 >
 * T_APPEND,	// 5 >>
 * T_LPARENTH,	// 6 (
 * T_RPARENTH,	// 7 )
 * T_OR,		// 8 ||
 * T_AND,		// 9  &&
 */
typedef enum e_symbol
{
	T_ARG,
	T_PIPE,
	T_INPUT,
	T_HEREDOC,
	T_OUTPUT,
	T_APPEND,
	T_LPARENTH,
	T_RPARENTH,
	T_OR,
	T_AND,
}					e_symbol;

/*
 * Tokens data structure
 */
typedef struct s_tokens
{
	e_symbol		symbol;
	char			*arg;
	struct s_tokens	*next;
}					t_tokens;

int					lexer(t_tokens **tokens, char *line);

// Stack utils functions
t_tokens			*ft_toknew(e_symbol symbol, t_tokens *next);
t_tokens			*ft_toklast(t_tokens *stack);
void				ft_tokadd_back(t_tokens **stack, t_tokens *new);
void				ft_tokclear(t_tokens *stack);
t_tokens			*ft_tokpop(t_tokens **stack);
char				*ft_substrc(char *str, int start, int end);
int					ft_toksize(t_tokens *tokens);

#endif
