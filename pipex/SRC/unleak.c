/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unleak.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:54:14 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/14 14:51:11 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	unleak(t_px *px)
{
	ft_free_map(px->env, ft_maplen(px->env));
	ft_free_split_map(px->cmd);
	if (px->pid)
		free(px->pid);
}
