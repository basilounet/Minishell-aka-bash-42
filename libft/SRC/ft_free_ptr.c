/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:25:35 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/22 14:09:20 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdarg.h>

void	*ft_free_ptr(int nb, ...)
{
	va_list	list;
	void	*ptr;

	va_start(list, nb);
	while (nb > 0)
	{
		ptr = va_arg(list, void *);
		if (ptr)
		{
			free(ptr);
			ptr = NULL;
		}
		nb--;
	}
	va_end(list);
	return (NULL);
}
