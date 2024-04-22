/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:57:38 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/17 20:09:40 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builts_in.h>
#include <minishell.h>

char	*ft_substrc(char *str, int start, int end)
{
	char	*new_str;
	int		i;

	i = 0;
	if (start > end)
		return (NULL);
	if (ft_isifs(str[end - 1]))
		end--;
	new_str = malloc(end - start + 2);
	if (!new_str)
		return (NULL);
	while (start + i < end)
	{
		new_str[i] = str[start + i];
		i++;
	}
	new_str[i] = 0;
	return (new_str);
}

int	is_evenly_quoted(char *str, int n)
{
	int	squote;
	int	dquote;
	int	i;

	squote = 0;
	dquote = 0;
	i = 0;
	while ((n && i < n) || (!n && str[i]))
	{
		if (str[i] == '\'' && dquote % 2 == 0)
			squote++;
		if (str[i] == '\"' && squote % 2 == 0)
			dquote++;
		i++;
	}
	if (squote % 2 || dquote % 2)
		return (0);
	return (1);
}

int	is_existing_dir(char *path)
{
	struct stat	stats;

	if (!path)
		return (0);
	stats = (struct stat){0};
	stat(path, &stats);
	if (S_ISDIR(stats.st_mode))
		return (1);
	return (0);
}

int	perr(int exit_code, int n, int bs, ...)
{
	va_list	args;
	char	*to_print;

	va_start(args, bs);
	if (bs)
		write(2, "baseshell: ", 11);
	while (n)
	{
		to_print = va_arg(args, char *);
		if (!to_print && n != 1)
		{
			va_arg(args, char *);
			n--;
		}
		else
			write(2, to_print, ft_strlen(to_print));
		n--;
	}
	write(2, "\n", 1);
	va_end(args);
	return (exit_code);
}
