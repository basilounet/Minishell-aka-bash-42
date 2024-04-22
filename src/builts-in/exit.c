/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:59:54 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/19 17:41:15 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builts_in.h>
#include <minishell.h>

int	ft_exit(t_ms *ms, char **args)
{
	long long	code;

	code = 0;
	if (!args[1])
		return (1); // exit 
	if (!ft_atoll(args[1], &code))
	{
		perr((t_perr){ms, 2, 3, 1}, "exit: ", args[1],
			": numeric argument required");
		return (1); // exit
	}
	if (args[2])
	{
		printf("exit\n");
		perr((t_perr){ms, 1, 1, 1}, "exit: too many arguments");
		return (0); // dont exit
	}
	ms->exit_code = (unsigned long long)code & 255;
	return (1); // exit
}
