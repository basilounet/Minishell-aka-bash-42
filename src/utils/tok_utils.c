/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangouil <gangouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:02:11 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/19 18:02:12 by gangouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <stdlib.h>

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

void	ft_tokadd_front(t_tokens **stack, t_tokens *new)
{
	if (!new)
	{
		if (!*stack)
		{
			*stack = new;
			return ;
		}
	}
	ft_toklast(new)->next = *stack;
	*stack = new;
}

int	ft_toksize(t_tokens *tokens)
{
	t_tokens	*tmp;
	int			i;

	i = 0;
	tmp = tokens;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	*tokens_to_string(t_tokens *tokens)
{
	char	*str;
	char	*quoted_str;

	str = NULL;
	while (tokens)
	{
		quoted_str = ft_strjoin3("\377", tokens->arg, "\377");
		if (!quoted_str)
		{
			if (str)
				free(str);
			return (NULL);
		}
		str = ft_str_reajoin(str, quoted_str, 1, 1);
		if (!str)
			return (NULL);
		tokens = tokens->next;
	}
	return (str);
}
