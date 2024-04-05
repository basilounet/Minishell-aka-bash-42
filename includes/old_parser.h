/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 00:29:25 by gangouil          #+#    #+#             */
/*   Updated: 2024/03/17 17:16:16 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OLD_PARSER_H
# define OLD_PARSER_H

# include <lexer.h>
# include <stdio.h>
# include <libft.h>
/*
 * Container type
 */
typedef enum e_type
{
	T_CMD,
	T_CTN,
}							e_type;

/*
 * Command data structure
 * args -> command arguments as a chained list
 * redirects -> inputs/outputs as a stack
 * pipe -> * to new cmd in case of pipe
 */
typedef struct s_command
{
	t_tokens				*args;
	t_tokens				*redirects;
	struct s_command		*pipe;
}							t_command;
/*
 * (Command) container data structure
 * Each container is separated by a logical operator
 * type -> describes the content of the union
 * cmd/ctn -> * to new container if there are parenthesis
 * 			  * to cmd otherwise
 * pipe -> * to new cmd in case of pipe
 * redirects -> inputs/outputs as a stack
 * operator -> indicates priorities (&&, || or NULL)
 * next_ctn -> * to the next container
 */
typedef struct s_container
{
	e_type					type;
	union
	{
		t_command			*cmd;
		struct s_container	*ctn;
	};
	t_command				*pipe;
	t_tokens				*redirects;
	e_symbol				operator;
	struct s_container		*next_ctn;
}							t_container;

t_container	*ft_ctnnew(e_type type, t_container *next);
t_container	*ft_ctnlast(t_container *stack);
void	ft_ctnadd_back(t_container **stack, t_container *new);
void	ft_ctnadd_front(t_container **stack, t_container *new);
void	ft_ctnclear(t_container *stack);
t_container	*parse_prompt(t_tokens *tokens);
t_container	*parse_logex(t_container *ctn, t_tokens **tokens);
int	parse_pipeline(t_container *ctn, t_tokens **tokens);
int	parse_command(t_container *ctn, t_tokens **tokens);
int	parse_brace(t_container *ctn, t_tokens **tokens);
int	parse_redlist(t_container *ctn, t_tokens **tokens, e_type type);

#endif
