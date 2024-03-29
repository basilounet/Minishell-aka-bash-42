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
#include <builts_in.h>

char	*ft_getenv(t_env *env, char *to_get)
{
	if (!env || !to_get)
		return (NULL);
	while (env && ft_strncmp(to_get, env->name, ft_strlen(to_get)))
		env = env->next;
	if (!env)
		return (NULL);
	return (env->var);
}

char	*ft_substrc(char *str, int start, int end)
{
	char	*new_str;
	int		i;

	i = 0;
	if (start > end)
		return (NULL);
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

int	is_evenly_quoted(char *str, int n)
{
	int	squote;
	int	dquote;
	int	i;

	squote = 0;
	dquote = 0;
	i = 0;
	while ((n && i < n) || (!n && str[i]))
	{
		if (str[i] == '\'' && dquote % 2 == 0)
			squote++;
		if (str[i] == '\"' && squote % 2 == 0)
			dquote++;
		i++;
	}
	if (squote % 2 || dquote % 2)
		return (0);
	return (1);
}