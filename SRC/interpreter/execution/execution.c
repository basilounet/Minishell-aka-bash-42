/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:50:58 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/02 14:53:11 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void    execute_node(t_ms *ms, t_node *node, int is_in_pipe)
{
    ft_printf("is_in_pipe : %d, is_last_pipe : %d\n\n", is_in_pipe, !is_in_pipe);
    if (node->type == T_TREE)
    {
        execute_node(ms, node->tree.left, is_in_pipe || node->tree.operator == T_PIPE);
        execute_node(ms, node->tree.right, is_in_pipe); 
    }
}

/*
A aa aa a && B bb b bbbb  | (C && D d && DD) | E e
( cat   <a >     b<d > b< f < a c && (cat < a ds> ad > f < d || ls )) | rev
*/