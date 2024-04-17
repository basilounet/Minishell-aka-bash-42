/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_outputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:24:53 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/17 13:59:06 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	unlink_here_docs(t_ms *ms)
{
	char	*name;
	int		i;

	i = 0;
	name = NULL;
	while (i < ms->heredoc_number)
	{
		name = ft_str_reajoin("/tmp/here_doc_", ft_itoa(i), 0, 1);
		if (name)
		{
			unlink(name);
			free(name);
		}
		i++;
	}
}

void	get_new_file(t_ms *ms, char **stop)
{
	char	*str;
	int		fd;

	str = expand_var(ms, *stop, (t_expand_args){0});
	ft_free_ptr(1, *stop);
	*stop = str;
	str = ft_str_reajoin("/tmp/here_doc_", ft_itoa(ms->heredoc_number), 0, 1);
	fd = open(str, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	ft_free_ptr(1, str);
	str = NULL;
	if (fd < 0)
		return ;
	g_sig = 0;
	while (1)
	{
		str = readline("> ");
		if (ft_strcmp(str, *stop) == 0)
			break ;
		if (g_sig == SIGINT)
		{
			ms->exit_code = 130;
			break ;
		}
		ft_putstr_fd(str, fd);
		ft_putstr_fd("\n", fd);
		ft_free_ptr(1, str);
	}
	if (!str && g_sig != SIGINT)
		ft_printf("baseshell: warning: here-document delimited by end-of-file \
(wanted `%s')\n", *stop);
	close(fd);
	ft_free_ptr(1, str);
}
