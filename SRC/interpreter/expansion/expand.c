/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:48:34 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/22 13:55:03 by bvasseur         ###   ########.fr       */
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

int	change_state(char c, int state, char *shld_remove, int i)
{
	int	new_state;

	new_state = state;
	if (c == '\"' && state == 0)
		new_state = 1;
	else if (c == '\'' && state == 0)
		new_state = 2;
	else if (c == '\"' && state == 1)
		new_state = 0;
	else if (c == '\'' && state == 2)
		new_state = 0;
	if (shld_remove && new_state != state)
		shld_remove[i] = 'y';
	return (new_state);
}

int	expanded_line_len(t_env *env, char *line, int state)
{
	char	*var_name;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (line[i])
	{
		state = change_state(line[i], state, NULL, 0);
		if (line[i] == '$' && state == 2)
			len += len_env_name(line + i + 1);
		else if (line[i] == '$' && state != 2)
		{
			var_name = ft_substr(line, i + 1, len_env_name(line + i + 1));
			len += ft_strlen(ft_getenv(env, var_name));
			if (var_name)
				free(var_name);
		}
		else
			len++;
		if (line[i++] == '$' && state != 2)
			i += len_env_name(line + i);
	}
	return (len);
}

char	*remove_quotes(char *str, char *should_remove)
{
	char	*line;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!str || !should_remove)
		return (ft_free_ptr(2, str, should_remove));
	line = ft_calloc(sizeof(char), ft_strlen(str) - ft_countc(str, 'y') + 1);
	if (!line)
		return (ft_free_ptr(2, str, should_remove));
	while (str[++i])
		if (should_remove[i] == 'n')
			line[j++] = str[i];
	ft_free_ptr(2, str, should_remove);
	return (line);
}

char	*expand_var(t_env *env, char *original, int state)
{
	char	*quote;
	char	*name;
	char	*line;
	int		i;

	line = ft_calloc(sizeof(char), expanded_line_len(env, original, 0) + 1);
	quote = ft_calloc(sizeof(char), expanded_line_len(env, original, 0) + 1);
	ft_memset(quote, 'n', expanded_line_len(env, original, 0) * (quote != NULL));
	i = 0;
	while (line && quote && original && original[i])
	{
		state = change_state(original[i], state, quote, ft_strlen(line));
		if (original[i] == '$' && state != 2)
		{
			name = ft_substr(original, i + 1, len_env_name(original + i + 1));
			ft_strncpy(line + ft_strlen(line), ft_getenv(env, name),
				ft_strlen(ft_getenv(env, name)) + 1);
			ft_free_ptr(1, name);
		}
		else
			line[ft_strlen(line)] = original[i];
		if (original[i++] == '$' && state != 2)
			i += len_env_name(original + i);
	}
	return (remove_quotes(line, quote));
}
