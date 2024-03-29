/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangouil <gangouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 04:25:39 by gangouil          #+#    #+#             */
/*   Updated: 2024/03/28 04:25:41 by gangouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <builts_in.h>

void    unset(t_env **env, char **args)
{
    int i;

    i = 1;
    while (*env && args[i])
    {
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
	tmp = (*env)->next;
	if (ft_strcmp((*env)->name, name) == 0)
	{
		ft_envdel_one(*env);
		*env = tmp;
		return ;
	}
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			next = tmp->next;
			ft_envdel_one(tmp);
			previous->next = next;
			return ;
		}
		previous = tmp;
		tmp = tmp->next;
	}
}