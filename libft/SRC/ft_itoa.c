/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 00:24:41 by marvin            #+#    #+#             */
/*   Updated: 2023/11/08 22:38:20 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int		sign;
	int		lennum;
	char	*dest;

	lennum = ft_lennum(n) - 1;
	if (n == 0)
		return (ft_strdup("0"));
	sign = (n < 0);
	dest = (char *)malloc(sizeof(char) * (lennum + sign + 1));
	if (dest == NULL)
		return (NULL);
	dest[sign + lennum--] = 0;
	while (lennum >= 0)
	{
		dest[lennum + sign] = ft_abs(n % 10) + 48;
		n /= 10;
		lennum--;
	}
	if (sign == 1)
		dest[0] = '-';
	return (dest);
}
