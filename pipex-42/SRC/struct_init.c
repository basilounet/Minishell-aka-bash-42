/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:53:54 by bvasseur          #+#    #+#             */
/*   Updated: 2024/02/26 15:13:16 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	init_px(t_px *px)
{
	px->env = NULL;
	px->cmd = NULL;
	px->pid = NULL;
	px->index = 0;
	px->total_cmd = 0;
}
