/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:48:16 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/23 17:28:41 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builts_in.h>
#include <minishell.h>

static int	cd_errors(t_env **env, char **args, t_ms *ms)
{
	if (!cd_set_pwd(env, ms))
		return (0);
	if (args[1] && args[2])
	{
		perr((t_perr){ms, 1, 1, 1}, "cd: too many arguments");
		return (0);
	}
	if (!ft_getenv(*env, "HOME") && !args[1])
	{
		perr((t_perr){ms, 1, 1, 1}, "cd: HOME not set");
		return (0);
	}
	return (1);
}

static int	cd_set_newpwd(t_env **env, t_ms *ms)
{
	char	cwd[512];

	if (ft_getenv(*env, "PWD"))
		replace_env(env, ft_envnew(ft_strdup("OLDPWD"),
				ft_strdup(ft_getenv(*env, "PWD")), NULL));
	ft_bzero(cwd, 512);
	if (!getcwd(cwd, 512))
	{
		perr((t_perr){ms, 1, 2, 1}, "cd: ", strerror(errno));
		return (0);
	}
	replace_env(env, ft_envnew(ft_strdup("PWD"), ft_strdup(cwd), NULL));
	return (1);
}

static int	go_to_dir(t_env **env, char *curpath, char *arg, t_ms *ms)
{
	if (!curpath)
		return (0);
	if (ft_strcmp(curpath, "-") == 0)
	{
		free(curpath);
		if (!ft_getenv(*env, "OLDPWD"))
		{
			perr((t_perr){ms, 1, 1, 1}, "cd: OLDPWD not set");
			return (0);
		}
		curpath = ft_strdup(ft_getenv(*env, "OLDPWD"));
		if (!curpath)
			return (0);
	}
	if (chdir(curpath) < 0)
	{
		perr((t_perr){ms, 1, 4, 1}, "cd: ", arg, ": ", strerror(errno));
		free(curpath);
		return (0);
	}
	free(curpath);
	if (!cd_set_newpwd(env, ms))
		return (0);
	return (1);
}

static char	*set_curpath(t_env **env, char *directory)
{
	char	*curpath;

	curpath = "\0";
	if (directory[0] == '.' || ft_strcmp(directory, "..") == 0)
		return (ft_strdup(directory));
	else
	{
		if (ft_getenv(*env, "CDPATH"))
			curpath = check_cdpath(env, directory);
		if (!curpath)
			return (NULL);
		if (ft_strcmp(curpath, "\0") == 0)
			return (ft_strdup(directory));
	}
	return (curpath);
}

int	cd(t_ms *ms, t_env **env, char **args)
{
	char	*curpath;
	char	*directory;
	int		success;

	if (!cd_errors(env, args, ms))
		return (0);
	if (args[1] && ft_strcmp(args[1], "-") == 0)
		return (go_to_dir(env, ft_strdup("-"), args[1], ms));
	if (ft_getenv(*env, "HOME") && !args[1])
		directory = ft_strdup(ft_getenv(*env, "HOME"));
	else
		directory = ft_strdup(args[1]);
	if (!directory)
		return (0);
	curpath = set_curpath(env, directory);
	if (curpath && curpath[0] != '/')
		success = go_to_dir(env, ft_strjoin3(ft_getenv(*env, "PWD"), "/",
					curpath), args[1], ms);
	else
		success = go_to_dir(env, ft_strdup(curpath), args[1], ms);
	ft_free_ptr(2, curpath, directory);
	if (success)
		ms->exit_code = 0;
	return (1);
}
