/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_outputs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:50:19 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/03 18:52:43 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parser.h>

void	get_new_file(t_ms *ms, char *stop)
{
	char	*str;
	char	*line;
	int		fd;

	str = ft_str_reajoin("here_doc_", ft_itoa(ms->heredoc_number), 0, 1);
	fd = open(str, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	ft_free_ptr(1, str);
	if (fd < 0)
		return ;
	line = readline("> ");
	while (ft_strcmp(line, stop))
	{
		str = ft_str_reajoin(expand_var(ms->env, line, 0, 0), "\n", 1, 0);
		ft_putstr_fd(str, fd);
		ft_free_ptr(2, line, str);
		line = readline("> ");
	}
	if (!line)
		ft_printf("baseshell: warning: here-document delimited by end-of-file (wanted `%s')\n",
			stop);
	////////////////////////////////////////////////////////////////////////////
	close(fd);
	ft_free_ptr(1, line);
}

static void	open_redirects(t_ms *ms, t_tokens *redirects)
{
	while (redirects)
	{
		if (redirects->symbol == T_HEREDOC)
		{
			get_new_file(ms, redirects->arg);
			redirects->arg = ft_str_reajoin("here_doc_",
					ft_itoa(ms->heredoc_number++), 0, 1);
		}
		if (redirects->symbol == T_OUTPUT)
			try_close_fd(open(redirects->arg, O_CREAT | O_WRONLY | O_TRUNC,
					0644));
		if (redirects->symbol == T_APPEND)
			try_close_fd(open(redirects->arg, O_CREAT | O_WRONLY | O_APPEND,
					0777));
		redirects = redirects->next;
	}
}

void	open_all_outputs(t_ms *ms, t_node *node)
{
	if (!node)
		return ;
	if (node->type == T_TREE)
	{
		open_all_outputs(ms, node->tree.left);
		open_all_outputs(ms, node->tree.right);
		open_redirects(ms, node->tree.redirects);
	}
	else
		open_redirects(ms, node->cmd.redirects);
}

void	update_outputs(t_node *node)
{
	if (!node)
		return ;
	if (node->type == T_TREE)
	{
		if (node->tree.operator!= T_PIPE)
			add_redirect_node(node->tree.left,
				get_output_tok(node->tree.redirects));
		add_redirect_node(node->tree.right,
			get_output_tok(node->tree.redirects));
		update_outputs(node->tree.left);
		update_outputs(node->tree.right);
	}
}
