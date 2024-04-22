/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangouil <gangouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:03:38 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/19 19:03:39 by gangouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builts_in.h>
#include <minishell.h>

static bool	is_wc_file(char *name, t_wc *wc, int is_end)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	if (is_end)
		len = ft_strlen(name) + ft_strlen(wc->wc);
	else
		len = ft_strlen(wc->wc) + ft_countc(wc->mask, '1');
	while (wc->wc[i] && i < len)
	{
		if (wc->mask[i] == '1')
		{
			i++;
			continue ;
		}
		if (wc->wc[i] != name[j])
			return (false);
		i++;
		j++;
	}
	if (is_end && name[j])
		return (false);
	return (true);
}

static char	get_next_char(t_wc *wc)
{
	int	i;

	while (wc)
	{
		if (wc->symbol == T_ARG)
		{
			i = 0;
			while (wc->wc[i])
			{
				if (wc->mask[i] != '1')
					return (wc->wc[i]);
				i++;
			}
		}
		wc = wc->next;
	}
	return ('\0');
}

static bool	is_in_wildcard(char *name, t_wc *wc)
{
	int		i;
	char	next_char;

	i = 0;
	while (wc->next)
	{
		if (wc->symbol == T_ARG)
			if (!is_wc_file(&name[i], wc, 0))
				return (false);
		if (wc->symbol == T_WILDCARD)
		{
			next_char = get_next_char(wc);
			i = ft_strrichr(name, next_char);
			if (next_char != name[i])
				return (false);
			while (wc->next && wc->symbol == T_WILDCARD)
				wc = wc->next;
			continue ;
		}
		wc = wc->next;
	}
	if (wc->symbol == T_ARG)
		if (!is_wc_file(&name[i], wc, 1))
			return (false);
	return (true);
}

bool	get_files(t_tokens **files, DIR *directory, t_wc *wc)
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
			perr((t_perr){wc->ms, 1, 2, 1}, "wildcards: ", strerror(errno));
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

void	sort_files(t_tokens *files)
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
