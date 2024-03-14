/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangouil <gangouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:36:42 by gangouil          #+#    #+#             */
/*   Updated: 2024/03/11 20:36:49 by gangouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <stdlib.h>

t_tokens	*ft_toknew(e_symbol symbol, t_tokens *next)
{
	t_tokens	*stack;

	stack = malloc(sizeof(t_tokens));
	if (!stack)
		return (NULL);
	stack->symbol = symbol;
	stack->arg = NULL;
	stack->next = next;
	return (stack);
}

t_tokens	*ft_toklast(t_tokens *stack)
{
	if (!stack)
		return (NULL);
	while (stack->next)
		stack = stack->next;
	return (stack);
}

void	ft_tokadd_back(t_tokens **stack, t_tokens *new)
{
	t_tokens	*last;

	if (!new)
		return ;
	if (!*stack)
	{
		*stack = new;
		return ;
	}
	last = ft_toklast(*stack);
	last->next = new;
}

/*void	ft_lstadd_front(t_tokens **stack, t_tokens *new)
{
	t_tokens	*new_last;

	if (!new)
		return ;
	new_last = ft_lstlast(new);
	new_last->next = *stack;
	*stack = new;
}*/

void	ft_tokclear(t_tokens *stack)
{
	t_tokens	*tmp;

	while (stack)
	{
		tmp = stack->next;
		if (stack->arg)
			free(stack->arg);
		free(stack);
		stack = tmp;
	}
	stack = NULL;
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
	stack = next;
}
