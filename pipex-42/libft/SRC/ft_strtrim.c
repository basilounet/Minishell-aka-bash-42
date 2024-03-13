/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:16:16 by marvin            #+#    #+#             */
/*   Updated: 2023/11/04 01:42:51 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_charset(const char *charset, char c)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(charset))
		if (charset[i++] == c)
			return (1);
	return (0);
}

static int	len_without_blank(char const *s, const char *charset)
{
	int	i;
	int	total_len;

	total_len = ft_strlen(s);
	i = total_len - 1;
	while (is_in_charset(charset, s[i]))
		i--;
	total_len -= (total_len - 1 - i);
	i = 0;
	while (is_in_charset(charset, s[i]))
		i++;
	total_len -= i;
	return (total_len);
}

char	*ft_strtrim(char const *s, char const *charset)
{
	char	*dest;
	int		totallen;
	int		i;
	int		j;

	j = 0;
	i = 0;
	totallen = len_without_blank(s, charset);
	if (totallen <= 0)
		return (ft_strdup(""));
	dest = (char *)malloc(sizeof(char) * (totallen + 1));
	if (dest == NULL)
		return (NULL);
	while (is_in_charset(charset, s[i]))
		i++;
	while (j < totallen)
	{
		dest[j] = s[i + j];
		j++;
	}
	dest[j] = 0;
	return (dest);
}
