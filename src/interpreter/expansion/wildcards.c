/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:39:24 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/19 18:38:06 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builts_in.h>
#include <minishell.h>

static DIR	*ft_open_directory(t_ms *ms)
{
	DIR		*directory;
	char	cwd[512];

	if (!getcwd(cwd, 512))
	{
		perr((t_perr){ms, 1, 2, 1}, "wildcards: ", strerror(errno));
		return (NULL);
	}
	directory = opendir(cwd);
	if (!directory)
		perr((t_perr){ms, 1, 2, 1}, "wildcards: ", strerror(errno));
	return (directory);
}

static char	*get_wc_result(t_tokens *files, DIR *dir, t_wc *wc, char *char_wc)
{
	char	*wc_result;

	if (!mask_wc(wc))
	{
		ft_tokclear(&files);
		ft_wcclear(&wc);
		closedir(dir);
		return (NULL);
	}
	if (!get_files(&files, dir, wc))
	{
		ft_tokclear(&files);
		closedir(dir);
		return (NULL);
	}
	sort_files(files);
	wc_result = tokens_to_string(files);
	ft_tokclear(&files);
	ft_wcclear(&wc);
	closedir(dir);
	if (!wc_result)
		wc_result = ft_strdup(char_wc);
	return (wc_result);
}

static bool	get_next_wc(t_wc **wc, char *char_wc, char *mask, int *i)
{
	char		*wc_part;
	int			j;

	j = *i;
	while (char_wc[*i])
	{
		if (char_wc[*i] == '*' && mask[*i] != '2')
			break ;
		(*i)++;
	}
	if (j == *i || *i == 0)
	{
		ft_wcnew_back(wc, T_WILDCARD, NULL);
		return (true);
	}
	wc_part = ft_substrc(char_wc, j, *i);
	if (!ft_wcnew_back(wc, T_ARG, wc_part))
	{
		ft_free_ptr(1, wc_part);
		return (false);
	}
	if (char_wc[*i])
		ft_wcnew_back(wc, T_WILDCARD, NULL);
	return (true);
}

static t_wc	*get_wc_parts(char *char_wc, char *mask)
{
	t_wc	*wc;
	int		i;

	i = 0;
	wc = NULL;
	while (char_wc[i])
	{
		if (!get_next_wc(&wc, char_wc, mask, &i))
		{
			ft_wcclear(&wc);
			return (NULL);
		}
		if (char_wc[i])
			i++;
		if (!char_wc[i] && char_wc[i - 1] == '*')
			ft_wcnew_back(&wc, T_WILDCARD, NULL);
	}
	return (wc);
}

char	*wildcards(t_ms *ms, char *char_wc)
{
	t_wc		*wc;
	t_tokens	*files;
	DIR			*directory;
	char		*mask;

	files = NULL;
	mask = ft_calloc(ft_strlen(char_wc) + 1, 1);
	if (!mask)
		return (NULL);
	quote_mask(char_wc, mask);
	wc = get_wc_parts(char_wc, mask);
	wc->ms = ms;
	free(mask);
	if (!wc)
		return (NULL);
	directory = ft_open_directory(ms);
	if (!directory)
	{
		ft_free_ptr(1, wc);
		return (NULL);
	}
	return (get_wc_result(files, directory, wc, char_wc));
}
