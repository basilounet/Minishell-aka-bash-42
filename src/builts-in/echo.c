/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 17:17:28 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/23 18:15:48 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	echo(t_ms *ms, char **args)
{
	int		i;
	int		newline;
	size_t	ncount;

	i = 1;
	newline = 1;
	ncount = ft_countc(args[1], 'n');
	if (args[1] && ncount > 0 && ncount == ft_strlen(args[1]) - 1
		&& args[1][0] == '-')
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
