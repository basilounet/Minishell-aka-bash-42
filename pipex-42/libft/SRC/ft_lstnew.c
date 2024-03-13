/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:43:04 by marvin            #+#    #+#             */
/*   Updated: 2023/12/13 14:57:45 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char *name, void *content)
{
	t_list	*new_el;

	new_el = (t_list *)malloc(sizeof(t_list));
	if (new_el == NULL)
		return (NULL);
	new_el->name = ft_strdup(name);
	if (!new_el->name)
	{
		free(new_el);
		return (NULL);
	}
	new_el->content = content;
	new_el->next = NULL;
	return (new_el);
}
