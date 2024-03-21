/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:36:42 by gangouil          #+#    #+#             */
/*   Updated: 2024/03/15 11:47:13 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <stdlib.h>

t_node	*ft_nodenew(e_type type, t_command cmd, t_tree tree)
{
	t_node	*stack;

	stack = ft_calloc(sizeof(t_node), 1);
	if (!stack)
		return (NULL);
	stack->type = type;
	if (cmd.args)
		stack->cmd = cmd;
	else
		stack->tree = tree;
	return (stack);
}

t_command	ft_cmdnew(t_tokens *args, t_tokens *redirects)
{
	t_command	cmd;

	cmd.args = args;
	cmd.redirects = redirects;
	return (cmd);
}