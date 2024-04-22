/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:21:11 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/16 14:00:23 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builts_in.h>
#include <libft.h>
#include <stddef.h>
#include <stdlib.h>

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

void	ft_envdel_one(t_env *stack)
{
	if (!stack)
		return ;
	if (stack->name)
		free(stack->name);
	if (stack->var)
		free(stack->var);
	free(stack);
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

int	ft_setenv(t_env **env, char *var, char *value)
{
	t_env	*new_env;

	new_env = ft_envnew(var, value, NULL);
	if (!new_env)
		return (0);
	ft_envadd_back(env, new_env);
	return (1);
}
