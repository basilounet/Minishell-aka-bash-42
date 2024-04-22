/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangouil <gangouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:05:14 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/19 18:05:15 by gangouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builts_in.h>
#include <libft.h>

char	*ft_getenv(t_env *env, char *to_get)
{
	if (!env || !to_get)
		return (NULL);
	while (env && ft_strcmp(to_get, env->name))
		env = env->next;
	if (!env)
		return (NULL);
	return (env->var);
}

char	*get_env_var(t_env *env, char *name)
{
	char	*dup_var;

	while (env)
	{
		if (ft_strcmp(name, env->name) == 0)
		{
			dup_var = ft_strdup(env->var);
			if (env->var)
			{
				free(env->var);
				env->var = NULL;
			}
			return (dup_var);
		}
		env = env->next;
	}
	return (NULL);
}

int	ft_envsize(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

void	ft_envadd_back(t_env **stack, t_env *new)
{
	t_env	*last;

	if (!new)
		return ;
	if (!*stack)
	{
		*stack = new;
		return ;
	}
	last = ft_envlast(*stack);
	last->next = new;
}

t_env	*ft_envlast(t_env *stack)
{
	t_env	*tmp;

	tmp = stack;
	if (!tmp)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
