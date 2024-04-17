/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 04:25:39 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/17 17:22:30 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builts_in.h>
#include <minishell.h>

void	unset(t_env **env, char **args)
{
	t_env	*tmp;
	int		i;

	i = 1;
	while (*env && args[i])
	{
		if (ft_strcmp((*env)->name, args[i]) == 0)
		{
			tmp = (*env)->next;
			ft_envdel_one(*env);
			*env = tmp;
		}
		else
			unset_name(env, args[i]);
		i++;
	}
}

void	unset_name(t_env **env, char *name)
{
	t_env	*tmp;
	t_env	*previous;
	t_env	*next;

	if (!*env)
		return ;
	tmp = *env;
	previous = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			next = tmp->next;
			ft_envdel_one(tmp);
			if (previous)
				previous->next = next;
			return ;
		}
		previous = tmp;
		tmp = tmp->next;
	}
}
