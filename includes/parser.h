/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangouil <gangouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 00:29:25 by gangouil          #+#    #+#             */
/*   Updated: 2024/03/13 17:48:08 by gangouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <lexer.h>

//Container type
typedef enum e_type
{
	T_CMD,
	T_CTN,
}	e_type;

// Command data structure
// args -> command arguments as a chained list
// redirects -> inputs/outputs as a stack
// pipe -> * to new cmd in case of pipe
typedef struct s_command
{
	t_tokens			*args;
	t_tokens			*redirects;
	struct s_command	pipe;
}	t_command;

// (Command) container data structure
// Each container is separated by a logical operator
// type -> describes the content of the union
// cmd/ctn -> * to new container if there are parenthesis
//			  cmd otherwise
// redirects -> inputs/outputs as a stack
// operator -> indicates priorities (&&, || or NULL)
// next_ctn -> * to the next container
typedef struct s_container
{
	e_type	type;
	union
	{
		t_command 			cmd;
		struct s_container	*ctn;
	};
	t_tokens	*redirects;
	e_symbol	operator;
	t_container	*next_ctn;
}	t_container;

#endif
