/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:19:37 by bvasseur          #+#    #+#             */
/*   Updated: 2023/11/27 21:26:07 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

static int	isconversion(int c)
{
	return (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'u'
		|| c == 'x' || c == 'X' || c == '%');
}

static void	ft_printf2(const char *s, va_list list, int *i, int *count)
{
	if (s[*i + 1] == '%')
		*count += write(1, "%", 1);
	else if (s[*i + 1] == 'c')
		*count += ft_putchar(va_arg(list, int));
	else if (s[*i + 1] == 's')
		*count += ft_putstr(va_arg(list, char *));
	else if (s[*i + 1] == 'd' || s[*i + 1] == 'i')
		*count += ft_putnbr(va_arg(list, int));
	else if (s[*i + 1] == 'X')
		*count += ft_put_malloc_free(ft_itob(va_arg(list, unsigned int),
					"0123456789ABCDEF"), &free);
	else if (s[*i + 1] == 'x')
		*count += ft_put_malloc_free(ft_itob(va_arg(list, unsigned int),
					"0123456789abcdef"), &free);
	else if (s[*i + 1] == 'u')
		*count += ft_putnbru(va_arg(list, unsigned int));
	else if (s[*i + 1] == 'p')
		*count += ft_putptr(va_arg(list, unsigned long));
	else
		count += write(1, "%", 1);
	if (isconversion(s[*i + 1]))
		*i += 1;
	*i += 1;
}

int	ft_printf(const char *s, ...)
{
	va_list	list;
	int		count;
	int		i;

	i = 0;
	count = 0;
	if (s == NULL)
		return (-1);
	va_start(list, s);
	while (s[i])
	{
		count += ft_strlentc(&s[i], '%');
		i += write(1, &s[i], ft_strlentc(&s[i], '%'));
		if (s[i] == '%')
			ft_printf2(s, list, &i, &count);
	}
	va_end(list);
	return (count);
}
