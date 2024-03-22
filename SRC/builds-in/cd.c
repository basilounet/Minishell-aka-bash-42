/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:48:16 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/19 17:20:09 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	cd(char *path)
{
	if (!path)
		return ;
	if (path[0] != '/')
		path = ft_str_reajoin(getcwd(NULL, 0), ft_strjoin("/", path), 1, 1);
	if (chdir(path))
        ft_printf("path not found\n");
}
