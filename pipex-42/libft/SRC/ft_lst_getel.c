/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_getel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:07:25 by bvasseur          #+#    #+#             */
/*   Updated: 2023/12/13 10:10:58 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lst_getel(t_list *lst, char *name)
{
	size_t	len_n;

	len_n = ft_strlen(name);
	while (lst && ft_strncmp(name, lst->name, len_n))
		lst = lst->next;
	return (lst);
}
