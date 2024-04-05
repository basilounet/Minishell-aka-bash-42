/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangouil <gangouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:03:30 by gangouil          #+#    #+#             */
/*   Updated: 2024/03/29 16:03:31 by gangouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exit_shell(int sig)
{
	(void)sig;
	g_exitcode = -2147483648;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("\0", 0);
	rl_redisplay();
}

void	set_interactive_mode(int set)
{
	if (set == 1)
	{
		signal(SIGINT, &exit_shell);
		signal(SIGQUIT, SIG_IGN);
		return ;
	}
}