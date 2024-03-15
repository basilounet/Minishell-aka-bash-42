/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:36:42 by gangouil          #+#    #+#             */
/*   Updated: 2024/03/15 11:47:13 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <stdlib.h>

t_tokens	*ft_toknew(e_symbol symbol, t_tokens *next)
{
	t_tokens	*stack;

	stack = ft_calloc(sizeof(t_tokens), 1);
	if (!stack)
		return (NULL);
	stack->symbol = symbol;
	stack->arg = NULL;
	stack->next = next;
	return (stack);
}

t_tokens	*ft_toklast(t_tokens *stack)
{
	t_tokens	*tmp;

	tmp = stack;
	if (!tmp)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	ft_tokadd_back(t_tokens **stack, t_tokens *new)
{
	t_tokens	*last;

	if (!new || !stack)
		return ;
	if (!*stack)
	{
		*stack = new;
		return ;
	}
	last = ft_toklast(*stack);
	last->next = new;
}

void	ft_tokadd_front(t_tokens **stack, t_tokens *new)
{
	if (!new || !stack)
		return ;
	ft_toklast(new)->next = *stack;
	*stack = new;
}

void	ft_tokclear(t_tokens *stack)
{
	t_tokens	*tmp;

	tmp = stack;
	while (tmp)
	{
		if (tmp->arg)
			free(tmp->arg);
		free(tmp);
		tmp = NULL;
		tmp = tmp->next;
	}
}

void	ft_tokpop(t_tokens *stack)
{
	t_tokens	*next;

	if (!stack)
		return ;
	next = stack->next;
	if (stack->arg)
		free(stack->arg);
	free(stack);
	stack = NULL;
	stack = next;
}
