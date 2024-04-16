/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:48:34 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/16 18:20:27 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*remove_quotes(t_expand exp_var, t_expand_args args)
{
	char	*line;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (args.ign_qte)
	{
		ft_free_ptr(1, exp_var.mask);
		return (exp_var.line);
	}
	line = ft_calloc(sizeof(char), ft_strlen(exp_var.line)
			- ft_countc(exp_var.mask, 'y') + 1);
	if (!line || !exp_var.line || !exp_var.mask)
	{
		ft_free_ptr(3, exp_var.line, exp_var.mask, line);
		return (NULL);
	}
	if (args.shld_ch_ifs)
		exp_var.line = change_ifs(exp_var.line, exp_var.mask);
	while (exp_var.line[++i])
		if (exp_var.mask[i] == 'n')
			line[j++] = exp_var.line[i];
	ft_free_ptr(2, exp_var.line, exp_var.mask);
	return (line);
}

int	expand_special_cases(t_ms *ms, char *str, t_expand *expand,
		t_expand_args args)
{
	char	*tmp_char;

	if (expand->state != 2 && str[expand->i] == '$' && str[expand->i
			+ 1] == '?')
	{
		tmp_char = ft_itoa(ms->exit_code);
		ft_strncpy(expand->line + ft_strlen(expand->line), tmp_char,
			ft_strlen(tmp_char) + 1);
		ft_free_ptr(1, tmp_char);
		return (1);
	}
	if (!args.expand_special_cases)
		return (0);
	if (expand->state == 0 && str[expand->i] == '~' && (str[expand->i
				+ 1] == ' ' || str[expand->i + 1] == 0) && (expand->i <= 0
			|| str[expand->i - 1] == ' '))
	{
		ft_strncpy(expand->line + ft_strlen(expand->line), ft_getenv(ms->env,
				"HOME"), ft_strlen(ft_getenv(ms->env, "HOME")) + 1);
		expand->i--;
		return (1);
	}
	return (0);
}

t_expand	expand(t_ms *ms, char *str, t_expand expand, t_expand_args args)
{
	if (!args.ign_qte)
		expand.state = change_state(str + expand.i, expand.state, expand.mask,
				ft_strlen(expand.line));
	if (expand_special_cases(ms, str, &expand, args))
		expand.i++;
	else if (str[expand.i] == '$' && len_env_name(str + expand.i + 1)
		&& expand.state != 2 && args.should_expand)
	{
		expand.name = ft_substr(str, expand.i + 1, len_env_name(str + expand.i
					+ 1));
		ft_strncpy(expand.line + ft_strlen(expand.line), ft_getenv(ms->env,
				expand.name), ft_strlen(ft_getenv(ms->env, expand.name)) + 1);
		ft_free_ptr(1, expand.name);
	}
	else
		expand.line[ft_strlen(expand.line)] = str[expand.i];
	if (str[expand.i++] == '$' && len_env_name(str + expand.i)
		&& expand.state != 2 && args.should_expand)
		expand.i += len_env_name(str + expand.i);
	return (expand);
}

char	*expand_var(t_ms *ms, char *str, t_expand_args args)
{
	t_expand	expand_var;

	ft_memset(&expand_var, 0, sizeof(t_expand));
	expand_var.line = ft_calloc(sizeof(char), exp_len(ms->env, str, args, 0)
			+ special_cases_total_len(ms, str, args) + 1);
	expand_var.mask = ft_calloc(sizeof(char), exp_len(ms->env, str, args, 0)
			+ special_cases_total_len(ms, str, args) + 1);
	if (!expand_var.line || !expand_var.mask || !str)
	{
		ft_free_ptr(2, expand_var.line, expand_var.mask);
		return (NULL);
	}
	ft_memset(expand_var.mask, 'n', exp_len(ms->env, str, args, 0)
		+ special_cases_total_len(ms, str, args));
	while (str[expand_var.i])
		expand_var = expand(ms, str, expand_var, args);
	return (remove_quotes(expand_var, args));
}
