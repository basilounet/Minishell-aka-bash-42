/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:57:38 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/18 14:05:38 by bvasseur         ###   ########.fr       */
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
		return (env[i] + len_env_name(env[i]) + 1);
	else if (!ft_strncmp(to_get, env[i], ft_strlen(to_get))
		&& env[i][ft_strlen(to_get)] != '=')
		return (ft_getenv(&env[i + 1], to_get));
	return (NULL);
}

char	*ft_substrc(char *str, int start, int end)
{
	char	*new_str;
	int		i;

	i = 0;
	if (str[end - 1] == ' ')
		end--;
	new_str = malloc(end - start + 2);
	if (!new_str)
		return (NULL);
	while (start + i < end)
	{
		new_str[i] = str[start + i];
		i++;
	}
	new_str[i] = 0;
	return (new_str);
}