/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ctns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:36:42 by gangouil          #+#    #+#             */
/*   Updated: 2024/03/15 11:39:58 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <stdlib.h>

t_container	*ft_ctnnew(e_type type, t_container *next)
{
	t_container	*stack;

	stack = ft_calloc(sizeof(t_container), 1);
	if (!stack)
		return (NULL);
	stack->type = type;
	stack->next_ctn = next;
	return (stack);
}

t_container	*ft_ctnlast(t_container *stack)
{
	t_container	*tmp;
	
	tmp = stack;
	if (!tmp)
		return (NULL);
	while (tmp->next_ctn)
		tmp = tmp->next_ctn;
	return (tmp);
}

void	ft_ctnadd_back(t_container **stack, t_container *new)
{
	t_container	*last;

	if (!new || !stack)
		return ;
	if (!*stack)
	{
		*stack = new;
		return ;
	}
	last = ft_ctnlast(*stack);
	last->next_ctn = new;
}

void	ft_ctnadd_front(t_container **stack, t_container *new)
{
	if (!new || !stack)
		return ;
	ft_ctnlast(new)->next_ctn = *stack;
	*stack = new;
}

void	ft_ctnclear(t_container *stack)
{
	t_container	*tmp;

	tmp = stack;
	while (tmp)
	{
		//if (type == T_CMD)
		//	call cmdclear (args, redirects, pipe)
		//else
		//	ft_ctnclear(tmp->ctn);
		ft_tokclear(tmp->redirects);
		free(tmp);
		tmp = NULL;
		tmp = tmp->next_ctn;
	}
}