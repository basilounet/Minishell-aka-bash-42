/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:54:12 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/14 17:30:52 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_itob(unsigned long n, const char *base_to)
{
	char	*converted_base;
	int		len_new;
	size_t	lb;

	len_new = 0;
	lb = ft_strlen(base_to);
	while (n / ft_power(lb, len_new) >= lb)
		len_new++;
	len_new++;
	converted_base = (char *)malloc(sizeof(char) * len_new + 1);
	if (converted_base == NULL)
		return (NULL);
	converted_base[len_new--] = 0;
	while (len_new >= 0)
	{
		converted_base[len_new] = base_to[ft_abs(n % lb)];
		n /= lb;
		len_new--;
	}
	return (converted_base);
}

int	ft_btoi(char *str, const char *base)
{
	int	len_number;
	int	len_base;
	int	nb;
	int	i;

	nb = 0;
	i = -1;
	len_number = ft_strlen(str);
	len_base = ft_strlen(base);
	while (str[++i] && i < 8)
		nb += ft_strlentc(base, str[i]) * ft_power(len_base, len_number - 1
				- i);
	return (nb);
}
