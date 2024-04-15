/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:48:34 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/12 13:10:40 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

int	change_state(char *str, int state, char *shld_remove, int i)
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
	if (shld_remove && (new_state != state || (state == 0 && str[0] == '$'
				&& (str[1] == '\'' || str[1] == '\"'))))
		shld_remove[i] = 'y';
	if (str[0] == '*' && state == 0)
		shld_remove[i] = 'w';
	return (new_state);
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

char	*remove_quotes(t_expand exp_var, t_expand_args args)
{
	char	*line;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (args.ign_qte)
	{
		ft_free_ptr(1, exp_var.qte);
		return (exp_var.line);
	}
	line = ft_calloc(sizeof(char), ft_strlen(exp_var.line)
			- ft_countc(exp_var.qte, 'y') + 1);
	if (!line || !exp_var.line || !exp_var.qte)
	{
		ft_free_ptr(3, exp_var.line, exp_var.qte, line);
		return (NULL);
	}
	if (args.shld_ch_ifs)
		exp_var.line = change_ifs(exp_var.line, exp_var.qte);
	while (exp_var.line[++i])
		if (exp_var.qte[i] == 'n')
			line[j++] = exp_var.line[i];
	ft_free_ptr(2, exp_var.line, exp_var.qte);
	return (line);
}

t_expand	expand(t_env *env, char *str, t_expand expand, t_expand_args args)
{
	if (!args.ign_qte)
		expand.state = change_state(str + expand.i, expand.state, expand.qte,
				ft_strlen(expand.line));
	if (str[expand.i] == '$' && len_env_name(str + expand.i + 1)
		&& expand.state != 2 && args.should_expand)
	{
		expand.name = ft_substr(str, expand.i + 1, len_env_name(str + expand.i
					+ 1));
		ft_strncpy(expand.line + ft_strlen(expand.line), ft_getenv(env,
				expand.name), ft_strlen(ft_getenv(env, expand.name)) + 1);
		ft_free_ptr(1, expand.name);
	}
	else
		expand.line[ft_strlen(expand.line)] = str[expand.i];
	if (str[expand.i++] == '$' && len_env_name(str + expand.i)
		&& expand.state != 2 && args.should_expand)
		expand.i += len_env_name(str + expand.i);
	return (expand);
}

char	*expand_var(t_env *env, char *str, t_expand_args args)
{
	t_expand	expand_var;

	ft_memset(&expand_var, 0, sizeof(t_expand));
	expand_var.line = ft_calloc(sizeof(char), exp_len(env, str, args, 0) + 1);
	expand_var.qte = ft_calloc(sizeof(char), exp_len(env, str, args, 0) + 1);
	ft_memset(expand_var.qte, 'n', exp_len(env, str, args, 0)
		* (expand_var.qte != NULL));
	while (expand_var.line && expand_var.qte && str && str[expand_var.i])
		expand_var = expand(env, str, expand_var, args);
	return (remove_quotes(expand_var, args));
}
