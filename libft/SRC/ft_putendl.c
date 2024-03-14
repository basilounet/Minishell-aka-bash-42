/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:20:31 by marvin            #+#    #+#             */
/*   Updated: 2023/11/08 19:07:43 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putendl(char const *s)
{
	if (s == NULL)
		s = (char *)"(null)";
	write(1, s, ft_strlen(s));
	write(1, "\n", 1);
	return (ft_strlen(s) + 1);
}
