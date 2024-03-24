/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_trees.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:36:42 by gangouil          #+#    #+#             */
/*   Updated: 2024/03/24 20:58:57 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <stdlib.h>

t_node	*ft_treenew(e_symbol ope, t_node *left, t_node *right, t_tokens *redirs)
{
	t_tree	stack;
	t_node	*node;

	stack.operator = ope;
	stack.left = left;
	stack.right = right;
	stack.redirects = redirs;
	node = ft_nodenew(T_TREE, (t_command){}, stack);
	if (!node)
	{
		if (left)
			free_node(left);
		if (right)
			free_node(right);
		ft_tokclear(&redirs);
		return (NULL);
	}
	return (node);
}