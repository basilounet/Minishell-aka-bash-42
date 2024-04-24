/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 02:07:51 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/23 17:29:11 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builts_in.h>
#include <minishell.h>

static char	**env_sort(char **env)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[j])
		{
			if (env[j + 1] && ft_strcmp(env[j], env[j + 1]) > 0)
			{
				tmp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (env);
}

static char	*env_formatted_values(t_env *env)
{
	int		i;
	char	*var;
	char	*char_env;

	i = 0;
	var = ft_calloc(ft_strlen(env->var) + 3, 1);
	if (!var)
		return (NULL);
	var[0] = '\"';
	while (env->var[i])
	{
		var[i + 1] = env->var[i];
		i++;
	}
	var[i + 1] = '\"';
	char_env = ft_strjoin3(env->name, "=", var);
	free(var);
	return (char_env);
}

static char	**env_formatted_array(t_env *env)
{
	char	**char_env;
	int		i;

	i = 0;
	char_env = ft_calloc(ft_envsize(env) + 1, sizeof(char *));
	if (!char_env)
		return (NULL);
	while (env)
	{
		if (!env->var)
			char_env[i] = ft_strdup(env->name);
		else
			char_env[i] = env_formatted_values(env);
		if (!char_env[i])
			return (NULL);
		env = env->next;
		i++;
	}
	return (char_env);
}

char	**env_list_to_array(t_env *env)
{
	char	**char_env;
	int		i;

	i = 0;
	char_env = ft_calloc(ft_envsize(env) + 1, sizeof(char *));
	if (!char_env)
		return (NULL);
	while (env)
	{
		if (env->var)
			char_env[i] = ft_strjoin3(env->name, "=", env->var);
		else
		{
			env = env->next;
			continue ;
		}
		if (!char_env[i])
			return (NULL);
		env = env->next;
		i++;
	}
	return (char_env);
}

int	print_export(t_env *env)
{
	char	**char_env;
	int		i;

	i = 0;
	char_env = env_formatted_array(env);
	if (!char_env)
		return (0);
	char_env = env_sort(char_env);
	while (char_env[i])
	{
		if (ft_strncmp(char_env[i], "_=", 2))
			printf("declare -x %s\n", char_env[i]);
		i++;
	}
	i = 0;
	while (char_env[i])
	{
		free(char_env[i]);
		i++;
	}
	free(char_env);
	return (1);
}
