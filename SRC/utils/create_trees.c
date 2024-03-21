/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ctns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:36:42 by gangouil          #+#    #+#             */
/*   Updated: 2024/03/17 17:04:38 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <stdlib.h>

t_node	*ft_treenew(e_symbol ope, t_node *left, t_node *right, t_tokens *redirs)
{
	t_tree	stack;

	stack.operator = ope;
	stack.left = left;
	stack.right = right;
	stack.redirects = redirs;
	return (ft_nodenew(T_TREE, (t_command){}, stack));
}