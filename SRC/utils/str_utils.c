/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:57:38 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/17 17:06:51 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_getenv(char **env, char *to_get)
{
	int	i;

	i = 0;
	if (!env || !to_get)
		return (NULL);
	while (ft_strncmp(to_get, env[i], ft_strlen(to_get)))
		i++;
	if (!env[i])
		return (NULL);
	if (!ft_strncmp(to_get, env[i], ft_strlen(to_get))
		&& env[i][ft_strlen(to_get)] == '=')
		return (env[i] + ft_strlentc(env[i], '=') + 1);
	else if (!ft_strncmp(to_get, env[i], ft_strlen(to_get))
		&& env[i][ft_strlen(to_get)] != '=')
		return (ft_getenv(&env[i + 1], to_get));
	return (NULL);
}
