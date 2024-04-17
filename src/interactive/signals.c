/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:03:30 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/16 13:41:25 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	display_nl(int sig)
{
	g_sig = sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("\0", 0);
	rl_redisplay();
}

void	exit_heredoc(int sig)
{
	char	c;

	g_sig = sig;
	c = '\n';
	ioctl(0, TIOCSTI, &c);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	set_interactive_mode(int set)
{
	if (set == 1)
	{
		signal(SIGINT, &display_nl);
		signal(SIGQUIT, SIG_IGN);
		return ;
	}
	if (set == 2)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		return ;
	}
	if (set == 3)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		return ;
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &exit_heredoc);
}
