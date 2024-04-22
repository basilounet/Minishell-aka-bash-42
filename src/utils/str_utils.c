/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:57:38 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/19 18:18:44 by bvasseur         ###   ########.fr       */
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
	if (stat(path, &stats) == -1)
		return (0);
	if (S_ISDIR(stats.st_mode))
		return (1);
	return (0);
}

void	perr(t_perr perr, ...)
{
	va_list	args;
	char	*to_print;

	if (perr.ms->error_occured)
		return ;
	va_start(args, perr);
	if (perr.bs)
		write(2, "baseshell: ", 11);
	while (perr.n)
	{
		to_print = va_arg(args, char *);
		if (!to_print && perr.n != 1)
		{
			va_arg(args, char *);
			perr.n--;
		}
		else
			write(2, to_print, ft_strlen(to_print));
		perr.n--;
	}
	write(2, "\n", 1);
	va_end(args);
	perr.ms->exit_code = perr.exit_code;
	perr.ms->error_occured = 42;
}
