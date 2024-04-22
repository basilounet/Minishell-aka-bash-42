/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:04:04 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/16 18:25:31 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*place_wildcards(t_ms *ms, t_expand exp_var)
{
	char	*line;
	char	*mask;

	mask = ft_calloc(ft_strlen(exp_var.line) + 1, 1);
	if (!mask)
		return (exp_var.line);
	if (!ft_countcnm(exp_var.line, '*', ft_strlen(exp_var.line), mask))
	{
		ft_free_ptr(1, mask);
		return (exp_var.line);
	}
	ft_free_ptr(1, mask);
	line = wildcards(ms, exp_var.line);
	if (!line)
		return (exp_var.line);
	ft_free_ptr(1, exp_var.line);
	return (line);
}

int	len_env_name(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len] && ((ft_isalnum(str[len])) || (str[len] == '_')))
		len++;
	return (len);
}

int	change_state(char *str, int state, char *mask, int i)
{
	int	new_state;

	new_state = state;
	if (str[0] == '\"' && state == 0)
		new_state = 1;
	else if (str[0] == '\'' && state == 0)
		new_state = 2;
	else if (str[0] == '\"' && state == 1)
		new_state = 0;
	else if (str[0] == '\'' && state == 2)
		new_state = 0;
	if (mask && (new_state != state || (state == 0 && str[0] == '$'
				&& (str[1] == '\'' || str[1] == '\"'))))
		mask[i] = 'y';
	return (new_state);
}

int	special_cases_total_len(t_ms *ms, char *str, t_expand_args args)
{
	t_expand	expand;
	int			len;

	ft_memset(&expand, 0, sizeof(t_expand));
	len = 0;
	while (str && str[expand.i])
	{
		if (!args.ign_qte)
			expand.state = change_state(str + expand.i, expand.state, NULL, 0);
		if (expand.state != 2 && str[expand.i] == '$' && str[expand.i \
			+ 1] == '?')
		{
			expand.i += 2;
			len += ft_lennum(ms->exit_code);
		}
		if (args.expand_special_cases && expand.state == 0
			&& str[expand.i] == '~' && (str[expand.i + 1] == ' ' || str[expand.i
					+ 1] == 0) && (expand.i <= 0 || str[expand.i - 1] == ' '))
			len += ft_strlen(ft_getenv(ms->env, "HOME"));
		if (str[expand.i])
			expand.i++;
	}
	return (len);
}

int	exp_len(t_env *env, char *line, t_expand_args args, int state)
{
	char	*var_name;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (line[i])
	{
		if (!args.ign_qte)
			state = change_state(line + i, state, NULL, 0);
		if (line[i] == '$' && len_env_name(line + i + 1) && state != 2
			&& args.should_expand)
		{
			var_name = ft_substr(line, i + 1, len_env_name(line + i + 1));
			len += ft_strlen(ft_getenv(env, var_name));
			ft_free_ptr(1, var_name);
		}
		else
			len++;
		if (line[i++] == '$' && len_env_name(line + i) && state != 2
			&& args.should_expand)
			i += len_env_name(line + i);
	}
	return (len);
}
