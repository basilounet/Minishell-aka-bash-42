/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_outputs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:50:19 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/26 15:43:58 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parser.h>

void    update_outputs(t_node *node)
{
    ;if (node->type == T_TREE)
    {
        if (node->tree.operator != T_PIPE)
            add_redirect_node(node->tree.left, get_output_tok(node->tree.redirects));
        add_redirect_node(node->tree.right, get_output_tok(node->tree.redirects));
        update_outputs(node->tree.left);
        update_outputs(node->tree.right);
    }
}
