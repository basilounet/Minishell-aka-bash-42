/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:39:24 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/09 13:04:44 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builts_in.h>
#include <minishell.h>

static DIR	*ft_open_directory(void)
{
	DIR		*directory;
	char	cwd[512];

	if (!getcwd(cwd, 512))
	{
		perr(1, 2, 1, "wildcards: ", strerror(errno));
		return (NULL);
	}
	directory = opendir(cwd);
	if (!directory)
		perr(1, 2, 1, "wildcards: ", strerror(errno));
	return (directory);
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

static bool	get_files(t_tokens **files, DIR *directory, t_wc *wc)
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

static void	quote_mask(char *wc, char *mask)
{
	int		i;
	bool	squote;
	bool	dquote;

	i = 0;
	squote = false;
	dquote = false;
	while (wc[i])
	{
		mask[i] = '0';
		if (!squote && wc[i] == '\"')
		{
			dquote = !dquote;
			mask[i] = '1';
		}
		else if (!dquote && wc[i] == '\'')
		{
			squote = !squote;
			mask[i] = '1';
		}
		else if (dquote || squote)
			mask[i] = '2';
		i++;
	}
	//printf("mask = %s\n", mask);
}

static bool	mask_wc(t_wc *wc)
{
	while (wc)
	{
		if (wc->symbol == T_ARG)
		{
			wc->mask = ft_calloc(ft_strlen(wc->wc) + 1, 1);
			if (!wc->mask)
				return (false);
			quote_mask(wc->wc, wc->mask);
		}
		wc = wc->next;
	}
	return (true);
}

static char	*get_wc_result(t_tokens *files, DIR *dir, t_wc *wc)
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

char	*wildcards(char *char_wc)
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
	free(mask);
	//print_tokens(wc, 0);
	//printf("\n");
	if (!wc)
		return (NULL);
	directory = ft_open_directory();
	if (!directory)
	{
		ft_free_ptr(1, wc);
		return (NULL);
	}
	return (get_wc_result(files, directory, wc));
}
