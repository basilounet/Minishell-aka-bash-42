/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 20:31:02 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/23 17:29:31 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builts_in.h>
#include <minishell.h>

void	replace_env(t_env **env, t_env *new_env)
{
	if (new_env->var || !ft_getenv(*env, new_env->name))
	{
		*env = unset_name(*env, new_env->name);
		ft_envadd_back(env, new_env);
		return ;
	}
	ft_free_ptr(2, new_env->name, new_env->var);
	free(new_env);
}

t_env	*parse_char_env(t_env *env, char *char_env, int j, int append)
{
	t_env	*new_env;
	char	*name;
	char	*var;

	name = ft_substr(char_env, 0, j);
	if (append == 0)
		var = ft_substr(char_env, j + 1, ft_strlen(char_env));
	else
		var = ft_str_reajoin(get_env_var(env, name), ft_substr(char_env, j + 2,
					ft_strlen(char_env)), 1, 1);
	new_env = ft_envnew(name, var, NULL);
	if (!new_env || !name || !var)
	{
		ft_free_ptr(3, new_env, name, var);
		return (NULL);
	}
	return (new_env);
}

static int	set_export_values(t_env **env, char *expand_arg)
{
	int		j;
	char	*name;
	t_env	*new_env;

	j = 0;
	while (expand_arg[j] && expand_arg[j] != '=' && expand_arg[j] != '+')
		j++;
	if (!expand_arg[j])
	{
		name = ft_substr(expand_arg, 0, j);
		if (!name)
			return (0);
		new_env = ft_envnew(name, NULL, NULL);
	}
	else if (expand_arg[j] == '=')
		new_env = parse_char_env(*env, expand_arg, j, 0);
	else
		new_env = parse_char_env(*env, expand_arg, j, 1);
	if (!new_env)
		return (0);
	replace_env(env, new_env);
	return (1);
}

static char	*is_export_valid(t_ms *ms, char *arg)
{
	int	i;

	i = 0;
	if (!arg || !arg[0] || arg[0] == '=' || (arg[0] >= '0' && arg[0] <= '9'))
	{
		perr((t_perr){ms, 1, 3, 1}, "export: `", arg,
			"': not a valid identifier");
		ft_free_ptr(1, arg);
		return (NULL);
	}
	while (arg[i])
	{
		if (i && ((arg[i] == '=') || (arg[i] == '+' && arg[i + 1 == '='])))
			break ;
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			perr((t_perr){ms, 1, 3, 1}, "export: `", arg,
				"': not a valid identifier");
			free(arg);
			return (NULL);
		}
		i++;
	}
	return (arg);
}

int	export(t_ms *ms, t_env **env, char **args)
{
	int		i;
	int		pass;
	char	*expand_arg;

	i = 1;
	pass = 1;
	if (!args[1])
		print_export(*env);
	while (args[i])
	{
		expand_arg = is_export_valid(ms, ft_strdup(args[i]));
		if (!expand_arg)
		{
			pass = 0;
			i++;
			continue ;
		}
		if (!set_export_values(env, expand_arg))
			return (0);
		free(expand_arg);
		i++;
	}
	if (pass)
		ms->exit_code = 0;
	return (pass);
}
