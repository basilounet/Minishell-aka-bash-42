/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:39:24 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/16 13:58:47 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builts_in.h>
#include <minishell.h>

static DIR	*ft_open_directory(t_env *env)
{
	DIR		*directory;
	char	cwd[512];

	if (is_existing_dir(ft_getenv(env, "PWD")))
		directory = opendir(ft_getenv(env, "PWD"));
	else
	{
		if (!getcwd(cwd, 512))
		{
			perr(1, 2, 1, "wildcards: ", strerror(errno));
			return (NULL);
		}
		directory = opendir(cwd);
	}
	if (!directory)
		perr(1, 2, 1, "wildcards: ", strerror(errno));
	return (directory);
}

static bool	is_in_wildcard(char *name, char *wc)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (wc[i] && name[j])
	{
		if (wc[i] != '*' && wc[i] != name[j])
			return (false);
		if (wc[i] == '*')
			j = ft_strrichr(name, wc[i + 1]);
		else
			j++;
		if (wc[i])
			i++;
	}
	if (wc[i] != '*' && (wc[i] || name[j]))
		return (false);
	return (true);
}

static bool	get_files(t_tokens **files, DIR *directory, char *wc)
{
	struct dirent	*curfile;
	int				i;
	t_tokens		*new_token;

	i = 0;
	while (i++ == 0 || curfile)
	{
		errno = 0;
		curfile = readdir(directory);
		if (!curfile && errno)
		{
			perr(1, 2, 1, "wildcards: ", strerror(errno));
			return (false);
		}
		if (!curfile)
			return (true);
		if (curfile->d_name[0] == '.' || !is_in_wildcard(curfile->d_name, wc))
			continue ;
		new_token = ft_toknew(T_ARG, ft_strdup(curfile->d_name), NULL);
		if (!new_token)
			return (false);
		ft_tokadd_back(files, new_token);
	}
	return (true);
}

static void	sort_files(t_tokens *files)
{
	t_tokens	*start;
	t_tokens	*tmp;
	char		*tmp_value;

	start = files;
	while (files)
	{
		tmp = start;
		while (tmp)
		{
			if (tmp->next && ft_strlowcmp(tmp->arg, tmp->next->arg) > 0)
			{
				tmp_value = tmp->arg;
				tmp->arg = tmp->next->arg;
				tmp->next->arg = tmp_value;
			}
			tmp = tmp->next;
		}
		files = files->next;
	}
}

char	*wildcards(t_env *env, char *wc)
{
	t_tokens	*files;
	DIR			*directory;
	char		*wc_result;

	files = NULL;
	directory = ft_open_directory(env);
	if (!directory)
		return (NULL);
	if (!get_files(&files, directory, wc))
	{
		ft_tokclear(&files);
		closedir(directory);
		return (NULL);
	}
	sort_files(files);
	wc_result = tokens_to_string(files);
	ft_tokclear(&files);
	closedir(directory);
	return (wc_result);
}
