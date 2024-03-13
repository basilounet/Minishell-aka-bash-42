/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_getindex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:35:11 by bvasseur          #+#    #+#             */
/*   Updated: 2024/01/17 17:45:21 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lst_getindex(t_list *lst, size_t index)
{
	size_t	i;

	i = 0;
	if (!lst || index > ft_lstsize(lst) - 1)
		return (0);
	while (lst && i < index)
	{
		lst = lst->next;
		i++;
	}
	return (lst);
}
