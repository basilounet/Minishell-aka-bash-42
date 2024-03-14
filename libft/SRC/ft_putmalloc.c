/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmalloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:22:38 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/14 17:32:05 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_put_malloc_free(char *s, void (*del)(void *))
{
	int	count;

	count = ft_putstr(s);
	del(s);
	return (count);
}
