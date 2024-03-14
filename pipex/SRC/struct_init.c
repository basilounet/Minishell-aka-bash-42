/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:53:54 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/14 14:51:09 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	init_px(t_px *px)
{
	px->env = NULL;
	px->cmd = NULL;
	px->pid = NULL;
	px->index = 0;
	px->total_cmd = 0;
	px->is_append = 0;
}
