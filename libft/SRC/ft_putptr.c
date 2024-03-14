/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:52:09 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/14 17:32:16 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_putptr(unsigned long ptr)
{
	char	*str;
	int		count;

	if (ptr == 0)
		return (ft_putstr("(nil)"));
	count = write(1, "0x", 2);
	str = ft_itob(ptr, "0123456789abcdef");
	count += ft_putstr(str);
	free(str);
	return (count);
}
