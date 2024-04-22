/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_wc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangouil <gangouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:23:03 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/17 13:23:17 by gangouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_wc	*ft_wcnew(t_symbol symbol, char *arg, t_wc *next)
{
	t_wc	*stack;

	stack = ft_calloc(sizeof(t_wc), 1);
	if (!stack)
		return (NULL);
	stack->symbol = symbol;
	stack->wc = arg;
	stack->next = next;
	return (stack);
}

t_wc	*ft_wclast(t_wc *stack)
{
	t_wc	*tmp;

	tmp = stack;
	if (!tmp)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	ft_wcadd_back(t_wc **stack, t_wc *new)
{
	t_wc	*last;

	if (!new)
		return ;
	if (!*stack)
	{
		*stack = new;
		return ;
	}
	last = ft_wclast(*stack);
	last->next = new;
}

bool	ft_wcnew_back(t_wc **tokens, t_symbol symbol, char *arg)
{
	t_wc	*new;

	new = ft_wcnew(symbol, arg, NULL);
	if (!new)
		return (false);
	ft_wcadd_back(tokens, new);
	return (true);
}

void	ft_wcclear(t_wc **stack)
{
	t_wc	*tmp;

	while (*stack)
	{
		tmp = (*stack)->next;
		if ((*stack)->wc)
			free((*stack)->wc);
		if ((*stack)->mask)
			free((*stack)->mask);
		free(*stack);
		*stack = tmp;
	}
	*stack = NULL;
}
