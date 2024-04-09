/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:48:16 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/19 17:20:09 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <builts_in.h>

static int	cd_errors(t_env **env, char **args)
{
	cd_set_pwd(env);
	if (args[1] && args[2])
	{
		perr(1, 1, 1, "cd: too many arguments");
		return (0);
	}
	if (!ft_getenv(*env, "HOME") && !args[1])
	{
		perr(1, 1, 1, "cd: HOME not set");
		return (0);
	}
	return (1);
}

static int	cd_set_newpwd(t_env **env)
{
	char 	*pwd_curpath;
	char	cwd[512];

	pwd_curpath = ft_str_reajoin("OLDPWD=", \
		ft_strdup(ft_getenv(*env, "PWD")), 0, 1);
	if (ft_getenv(*env, "PWD"))
		if (!export(env, (char *[]){"export", pwd_curpath, NULL}))
			return (0); //malloc error
	free(pwd_curpath);
	ft_bzero(cwd, 512);
	if (!getcwd(cwd, 512))
	{
		perr(1, 2, 1, "cd: ", strerror(errno)); // need ms->exit_code =
		return (0);
	}
	pwd_curpath = ft_strjoin("PWD=", cwd);
	if (!pwd_curpath || !export(env, (char *[]){"export", pwd_curpath, NULL}))
	{
		if (pwd_curpath)
			free(pwd_curpath);
		return (0); //malloc error
	}
	free(pwd_curpath);
	return (1);
}

static int	go_to_dir(t_env **env, char *curpath, char *arg)
{
	if (!curpath)
		return (0); //malloc error
	if (ft_strcmp(curpath, "-") == 0)
	{
		free(curpath);
		if (!ft_getenv(*env, "OLDPWD"))
		{
			perr(1, 1, 1, "cd: OLDPWD not set");
			return (0);
		}
		curpath = ft_strdup(ft_getenv(*env, "OLDPWD"));
		if (!curpath)
			return (0); //malloc error
	}
	if (chdir(curpath) < 0)
	{
		perr(1, 4, 1, "cd: ", arg, ": ", strerror(errno));
		free(curpath);
		return (0);
	}
	free(curpath);
	if (!cd_set_newpwd(env))
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

int	cd(t_env **env, char **args)
{
	char	*curpath;
	char	*directory;
	int		success;

	if (!cd_errors(env, args))
		return (0);
	if (args[1] && ft_strcmp(args[1], "-") == 0)
		return (go_to_dir(env, ft_strdup("-"), args[1]));
	if (ft_getenv(*env, "HOME") && !args[1])
		directory = ft_strdup(ft_getenv(*env, "HOME"));
	else
		directory = ft_strdup(args[1]);
	if (!directory)
		return (0); // malloc error
	curpath = set_curpath(env, directory);
	if (curpath && curpath[0] != '/')
		success = go_to_dir(env, \
			ft_strjoin3(ft_getenv(*env, "PWD"), "/", curpath), args[1]);
	else
		success = go_to_dir(env, ft_strdup(curpath), args[1]);
	if (curpath)
		free(curpath);
	free(directory);
	return (success);
}
