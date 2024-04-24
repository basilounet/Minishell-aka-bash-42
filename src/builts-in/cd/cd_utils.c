/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:00:11 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/23 17:28:27 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builts_in.h>
#include <minishell.h>

int	cd_set_pwd(t_env **env, t_ms *ms)
{
	char	cwd[512];
	char	*pwd;

	pwd = ft_getenv(*env, "PWD");
	if (pwd && is_existing_dir(pwd))
		return (1);
	if (!getcwd(cwd, 512))
	{
		perr((t_perr){ms, 1, 2, 1}, "cd: ", strerror(errno));
		return (0);
	}
	replace_env(env, ft_envnew(ft_strdup("PWD"), ft_strdup(cwd), NULL));
	return (1);
}

static char	*is_cdpath(char **paths, char *directory)
{
	char	*path_i;
	int		i;

	i = 0;
	while (paths[i])
	{
		path_i = ft_strjoin3(paths[i], "/", directory);
		if (!path_i)
		{
			ft_free_map(paths, ft_maplen(paths));
			return (NULL);
		}
		if (is_existing_dir(path_i))
			return (path_i);
		free(path_i);
		i++;
	}
	return ("\0");
}

char	*check_cdpath(t_env **env, char *directory)
{
	char	**paths;
	char	*cdpath;
	char	*pass;

	cdpath = ft_getenv(*env, "CDPATH");
	paths = ft_split(cdpath, ':');
	if (!paths)
		return (NULL);
	pass = is_cdpath(paths, directory);
	if (!pass)
		return (NULL);
	ft_free_map(paths, ft_maplen(paths));
	return (pass);
}
