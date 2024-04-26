/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 17:17:28 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/26 12:56:56 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	echo(t_ms *ms, char **args)
{
	int	newline;
	int	i;

	i = 1;
	newline = 1;
	while (args[i] && ft_countc(args[i], 'n') > 0 && ft_countc(args[i],
			'n') == ft_strlen(args[i]) - 1 && args[i][0] == '-')
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", 1);
	ms->exit_code = 0;
}
