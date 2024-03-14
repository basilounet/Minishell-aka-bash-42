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

#include <parser.h>
#include <stdlib.h>

t_container	*ft_ctnnew(e_type type, t_container *next)
{
	t_container	*stack;

	stack = malloc(sizeof(t_container));
	if (!stack)
		return (NULL);
	stack->redirects = NULL;
	stack->operator = NULL;
	stack->next_ctn = next;
	return (stack);
}

t_container	*ft_ctnlast(t_container *stack)
{
	if (!stack)
		return (NULL);
	while (stack->next)
		stack = stack->next_ctn;
	return (stack);
}

void	ft_ctnadd_back(t_container **stack, t_container *new)
{
	t_container	*last;

	if (!new)
		return ;
	if (!*stack)
	{
		*stack = new;
		return ;
	}
	last = ft_ctnlast(*stack);
	last->next_ctn = new;
}

/*void	ft_lstadd_front(t_container **stack, t_container *new)
{
	t_container	*new_last;

	if (!new)
		return ;
	new_last = ft_lstlast(new);
	new_last->next = *stack;
	*stack = new;
}*/

void	ft_ctnclear(t_container *stack)
{
	t_container	*tmp;

	ft_tokclear(stack->redirects);
	while (stack)
	{
		tmp = stack->next_ctn;
		//if (type == T_CMD)
		//	call cmdclear (args, redirects, pipe)
		free(stack);
		stack = tmp;
	}
	stack = NULL;
}