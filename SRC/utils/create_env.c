/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangouil <gangouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:21:11 by gangouil          #+#    #+#             */
/*   Updated: 2024/03/23 14:21:12 by gangouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builts_in.h>
#include <stddef.h>
#include <stdlib.h>
#include <libft.h>

t_env	*ft_envnew(char *name, char *var, t_env *next)
{
	t_env	*stack;

	stack = ft_calloc(sizeof(t_env), 1);
	if (!stack)
		return (NULL);
	stack->name = name;
	stack->var = var;
	stack->next = next;
	return (stack);
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

void	ft_envdel_one(t_env	*stack)
{
	if (!stack)
		return ;
	if (stack->name)
		free(stack->name);
	if (stack->var)
		free(stack->var);
	free(stack);
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

int	ft_setenv(t_env **env, char *var, char *value)
{
	t_env	*new_env;

	new_env = ft_envnew(var, value, NULL);
	if (!new_env)
		return (0);
	ft_envadd_back(env, new_env);
	return (1);
}

void	ft_envclear(t_env *stack)
{
	t_env	*tmp;

	while (stack)
	{
		tmp = stack->next;
		if (stack->name)
			free(stack->name);
		if (stack->var)
			free(stack->var);
		free(stack);
		stack = tmp;
	}
	stack = NULL;
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