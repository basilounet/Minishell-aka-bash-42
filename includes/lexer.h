/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:18:25 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/19 18:39:46 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <libft.h>
# include <stdbool.h>
# include <stddef.h>

/*
 * Tokens types
 * T_ARG,			// 0 cat
 * T_PIPE,			// 1 |
 * T_OUTPUT,		// 2 >
 * T_APPEND,		// 3 >>
 * T_INPUT,			// 4 <
 * T_HEREDOC,		// 5 <<
 * T_FINAL_OUTPUT,	// 6 >	FINAL
 * T_FINAL_APPEND,	// 7 >>	FINAL
 * T_FINAL_INPUT,	// 8 <	FINAL
 * T_FINAL_HEREDOC,	// 9 <<	FINAL
 * T_LPARENTH,		// 10 (
 * T_RPARENTH,		// 11 )
 * T_OR,			// 12 ||
 * T_AND,			// 13  &&
 */
typedef enum e_symbol
{
	T_ARG,
	T_PIPE,
	T_OUTPUT,
	T_APPEND,
	T_INPUT,
	T_HEREDOC,
	T_FINAL_OUTPUT,
	T_FINAL_APPEND,
	T_FINAL_INPUT,
	T_FINAL_HEREDOC,
	T_LPARENTH,
	T_RPARENTH,
	T_OR,
	T_AND,
	T_WILDCARD,
	T_EXPAND,
}					t_symbol;

/*
 * Tokens data structure
 */
typedef struct s_tokens
{
	t_symbol		symbol;
	char			*arg;
	struct s_tokens	*next;
}					t_tokens;

/*========== TOKENS ==========*/

t_tokens			*ft_toknew(t_symbol symbol, char *arg, t_tokens *next);
bool				ft_toknew_back(t_tokens **tokens, t_symbol symbol,
						char *arg);
t_tokens			*ft_toklast(t_tokens *stack);
void				ft_tokadd_back(t_tokens **stack, t_tokens *new);
void				ft_tokadd_front(t_tokens **stack, t_tokens *new);
void				ft_tokclear(t_tokens **stack);
t_tokens			*ft_tokpop(t_tokens **stack);
int					ft_toksize(t_tokens *tokens);

#endif
