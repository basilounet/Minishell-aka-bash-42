/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:54:02 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/08 13:37:32 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	env(t_ms *ms, t_env *env, char **args)
{
	if (args[1])
	{
		perr((t_perr){ms, 127, 3, 0}, "env: ", \
			args[1], ": No such file or directory");
		return ;
	}
	while (env)
	{
		if (env->var)
			printf("%s=%s\n", env->name, env->var);
		env = env->next;
	}
	ms->exit_code = 0;
}
