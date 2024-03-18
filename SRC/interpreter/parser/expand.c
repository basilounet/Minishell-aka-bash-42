/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:12:41 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/18 12:55:17 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*replace_env_v(t_ms *ms, char *str, char *original, int *i)
{
	int		len;
	char	*var_name;

	len = 0;
	(*i) += 1;
	while (original[(*i) + len] && ((ft_isalnum(original[(*i) + len])) || (original[(*i) + len] == '_')))
		len++;
    var_name = ft_substr(original, (*i), len);
	//ft_printf("str : %s, original : %s, len : %d, i : %d, var_name :%s\nenv : %s\n", str , original, len, *i, var_name, ft_getenv(ms->env, var_name));
	str = ft_str_reajoin(str, ft_strdup(ft_getenv(ms->env, var_name)), 1, 1);
	(*i) += len;
	if (var_name)
		free(var_name);
	return (str);
}

char	*expand_var(t_ms *ms, char *original)
{
	char	*str;
	int		i;
	int		state;

	if (!original || !*original)
		return (NULL);
	state = 0;
	i =  ft_strlentc(original, '$');
	str = ft_substr(original, 0, i);
	while (original[i])
	{
		if (original[i] == '$')
			str = replace_env_v(ms, str, original, &i);
		str = ft_str_reajoin(str, ft_substr(original, i, ft_strlentc(original + i, '$')), 1, 1);
		i +=  ft_strlentc(original + i, '$');
	}
	return (str);
}
