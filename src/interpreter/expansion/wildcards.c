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

static char	get_next_char(t_tokens *wc)
{
	while (wc)
	{
		if (wc->symbol == T_ARG)
			return (wc->arg[0]);
		wc = wc->next;
	}
	return ('\0');
}

static bool	is_wc_file(char *name, char *wc, char *mask)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(wc) + ft_countc(mask, '1');
	while (wc[i] && i < len)
	{
		if (mask[i] == '1')
		{
			i++;
			continue ;
		}
		if (wc[i] != name[j])
			return (false);
		i++;
		j++;
	}
	return (true);
}

static bool	is_in_wildcard(char *name, t_tokens *wc, char *mask)
{
	int		i;
	char	next_char;

	i = 0;
	while (wc)
	{
		if (wc->symbol == T_ARG)
			if (!is_wc_file(&name[i], wc->arg, mask))
				return (false);
		if (wc->symbol == T_WILDCARD)
		{
			next_char = get_next_char(wc);
			i = ft_strrichr(name, next_char);
			if (next_char != name[i])
				return (false);
			while (wc && wc->symbol == T_WILDCARD)
				wc = wc->next;
			continue ;
		}
		wc = wc->next;
	}
	if (name[i + 1])
		return (false);
	return (true);
}

static bool	get_files(t_tokens **files, DIR *directory, t_tokens *wc, char *mask)
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
		if (curfile->d_name[0] == '.' || !is_in_wildcard(curfile->d_name, wc, \
			mask))
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

static char	*get_wc_result(t_tokens *files, DIR *dir, t_tokens *wc, char *mask)
{
	char	*wc_result;

	if (!get_files(&files, dir, wc, mask))
	{
		ft_tokclear(&files);
		closedir(dir);
		return (NULL);
	}
	sort_files(files);
	wc_result = tokens_to_string(files);
	free(mask);
	ft_tokclear(&files);
	ft_tokclear(&wc);
	closedir(dir);
	return (wc_result);
}

static bool	get_next_wc(t_tokens **wc, char *char_wc, char *mask, int *i)
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
		ft_toknew_back(wc, T_WILDCARD, NULL);
		return (true);
	}
	wc_part = ft_substrc(char_wc, j, *i);
	if (!ft_toknew_back(wc, T_ARG, wc_part))
	{
		ft_free_ptr(1, wc_part);
		return (false);
	}
	if (char_wc[*i])
		ft_toknew_back(wc, T_WILDCARD, NULL);
	return (true);
}

static t_tokens	*get_wc_parts(char *char_wc, char *mask)
{
	t_tokens	*wc;
	int			i;

	i = 0;
	wc = NULL;
	while (char_wc[i])
	{
		if (!get_next_wc(&wc, char_wc, mask, &i))
		{
			ft_tokclear(&wc);
			return (NULL);
		}
		if (char_wc[i])
			i++;
		if (!char_wc[i] && char_wc[i - 1] == '*')
			ft_toknew_back(&wc, T_WILDCARD, NULL);
	}
	return (wc);
}

char	*wildcards(char *char_wc)
{
	t_tokens	*wc;
	t_tokens	*files;
	DIR			*directory;
	char		*mask;

	files = NULL;
	mask = ft_calloc(ft_strlen(char_wc) + 1, 1);
	if (!mask)
		return (NULL);
	quote_mask(char_wc, mask);
	wc = get_wc_parts(char_wc, mask);
	//print_tokens(wc, 0);
	//printf("\n");
	if (!wc)
	{
		ft_free_ptr(2, mask, wc);
		return (NULL);
	}
	directory = ft_open_directory();
	if (!directory)
	{
		ft_free_ptr(2, mask, wc);
		return (NULL);
	}
	return (get_wc_result(files, directory, wc, mask));
}
