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

static t_expand	get_final_expand(t_ms *ms, t_expand exp_var, t_expand_args args)
{
	char	*pre_wc;

	exp_var.is_wildcard = 0;
	if (exp_var.line && args.shld_ch_ifs)
		exp_var.line = change_ifs(exp_var.line, exp_var.mask);
	pre_wc = ft_strdup(exp_var.line);
	if (exp_var.line && args.expand_wc)
		exp_var.line = place_wildcards(ms, exp_var);
	if (ft_strcmp(pre_wc, exp_var.line) == 0)
	{
		if (exp_var.line && !args.ign_qte)
			exp_var.line = remove_quotes(exp_var, args);
	}
	else if (!exp_var.is_expand)
		exp_var.is_wildcard = 1;
	ft_free_ptr(2, pre_wc, exp_var.mask);
	return (exp_var);
}

char	*remove_quotes(t_expand exp_var, t_expand_args args)
{
	char	*line;
	int		i;
	int		j;

	(void)args;
	i = -1;
	j = 0;
	line = ft_calloc(sizeof(char), ft_strlen(exp_var.line)
			- ft_countc(exp_var.mask, 'y') + 1);
	if (!line || !exp_var.line || !exp_var.mask)
	{
		ft_free_ptr(2, exp_var.line, line);
		return (NULL);
	}
	while (exp_var.line[++i])
		if (exp_var.mask[i] == 'n')
			line[j++] = exp_var.line[i];
	ft_free_ptr(1, exp_var.line);
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
		expand.is_expand = 1;
	}
	else
		expand.line[ft_strlen(expand.line)] = str[expand.i];
	if (str[expand.i++] == '$' && len_env_name(str + expand.i)
		&& expand.state != 2 && args.should_expand)
		expand.i += len_env_name(str + expand.i);
	return (expand);
}

t_expand	expand_var(t_ms *ms, char *str, t_expand_args args)
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
		return ((t_expand){0});
	}
	ft_memset(expand_var.mask, 'n', exp_len(ms->env, str, args, 0)
		+ special_cases_total_len(ms, str, args));
	while (str[expand_var.i])
		expand_var = expand(ms, str, expand_var, args);
	return (get_final_expand(ms, expand_var, args));
}
