/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:36:42 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/16 14:01:17 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <stdlib.h>

t_tokens	*ft_toknew(t_symbol symbol, char *arg, t_tokens *next)
{
	t_tokens	*stack;

	stack = ft_calloc(sizeof(t_tokens), 1);
	if (!stack)
		return (NULL);
	stack->symbol = symbol;
	stack->arg = arg;
	stack->next = next;
	return (stack);
}

void	ft_tokclear(t_tokens **stack)
{
	t_tokens	*tmp;

	while (*stack)
	{
		tmp = (*stack)->next;
		if ((*stack)->arg)
			free((*stack)->arg);
		free(*stack);
		*stack = tmp;
	}
	*stack = NULL;
}

t_tokens	*ft_tokpop(t_tokens **stack)
{
	t_tokens	*current_token;

	if (!stack || !*stack)
		return (NULL);
	current_token = *stack;
	*stack = (*stack)->next;
	current_token->next = NULL;
	return (current_token);
}
