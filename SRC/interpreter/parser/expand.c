/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:12:41 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/18 18:16:07 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	len_env_name(char *str)
{
	int	len;

	len = 0;
	while (str[len] && ((ft_isalnum(str[len])) || (str[len] == '_')))
		len++;
	return (len);
}

char	*replace_env_var(t_ms *ms, char *str, char *original, int *i)
{
	int		len;
	char	*var_name;

	len = 0;
	(*i) += 1;
	len = len_env_name(original + *i);
	var_name = ft_substr(original, (*i), len);
	str = ft_str_reajoin(str, ft_strdup(ft_getenv(ms->env, var_name)), 1, 1);
	(*i) += len - 1;
	if (var_name)
		free(var_name);
	return (str);
}

int	change_state(char *original, int i, int state)
{
	if (original[i] == '\"' && state == 0)
		return (1);
	if (original[i] == '\'' && state == 0)
		return (2);
	if (original[i] == '\"' && state == 1)
		return (0);
	if (original[i] == '\'' && state == 2)
		return (0);
	return (state);
}

char	*remove_quotes(char *str)
{
	int		state;
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	state = 0;
	new = NULL;
	if (!str)
		return (NULL);
	while (str[i])
	{
		state = change_state(str, i, state);
		if ((str[i] == '\"' && (state == 0 || state == 1)) || (str[i] == '\''
				&& (state == 0 || state == 2)))
		{
			new = ft_str_reajoin(new, ft_substr(str, j, i - j), 1, 1);
			j = i + 1;
		}
		i++;
	}
	new = ft_str_reajoin(new, ft_substr(str, j, i - j), 1, 1);
	free(str);
	return (new);
}

char	*expand_special_cases(t_ms *ms, char c, char *str, int *j)
{
	if (!(c == '~'))
		return (str);
	*j += 1;
	if (c == '~')
		return (ft_str_reajoin(str, ft_getenv(ms->env, "HOME"), 1, 0));
	return (str);
}

char	*expand_var(t_ms *ms, char *original, int state)
{
	char	*str;
	int		i;
	int		j;

	if (!original || !*original)
		return (NULL);
	i = -1;
	j = 0;
	str = NULL;
	while (original[++i])
	{
		state = change_state(original, i, state);
		if (original[i] == '$' || original[i] == '~')
		{
			str = ft_str_reajoin(str, ft_substr(original, j, i - j), 1, 1);
			if (state == 0)
				str = expand_special_cases(ms, original[i], str, &j);
			if (state != 2)
				str = replace_env_var(ms, str, original, &i);
			j = i + (state != 2);
		}
	}
	str = ft_str_reajoin(str, ft_substr(original, j, i - j), 1, 1);
	return (remove_quotes(str));
}

int	check_quotes(char *str)
{
	int	state;
	int	i;

	i = 0;
	state = 0;
	while (str[i])
		state = change_state(str, i++, state);
	return (state == 0);
}
