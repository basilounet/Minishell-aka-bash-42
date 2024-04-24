/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts_in_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:10:17 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/23 17:28:18 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_built_in(char *command)
{
	return (!ft_strcmp(command, "echo") || !ft_strcmp(command, "cd")
		|| !ft_strcmp(command, "pwd") || !ft_strcmp(command, "export")
		|| !ft_strcmp(command, "unset") || !ft_strcmp(command, "env")
		|| !ft_strcmp(command, "exit"));
}

int	env_array_to_list(t_env **env, char **char_env)
{
	int		i;
	int		j;
	t_env	*new_env;

	i = 0;
	while (char_env[i])
	{
		j = 0;
		while (char_env[i][j] != '=')
			j++;
		new_env = parse_char_env(*env, char_env[i], j, 0);
		if (!new_env)
		{
			ft_envclear(*env);
			return (0);
		}
		ft_envadd_back(env, new_env);
		i++;
	}
	return (1);
}
