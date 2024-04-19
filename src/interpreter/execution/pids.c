/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pids.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:49:25 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/19 14:19:12 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_pid(int *pids)
{
	int	i;

	ft_printf("pids : ");
	if (!pids)
	{
		ft_printf("\n");
		return ;
	}
	i = 0;
	while (pids[i] != -1)
		ft_printf("%d, ", pids[i++]);
	ft_printf("%d\n", pids[i]);
}

int	pids_len(int *pids)
{
	int	len;

	if (!pids)
		return (1);
	len = 0;
	while (pids[len] != -1)
		len++;
	return (len + 1);
}

int	*add_pid_space(t_ms *ms, int *pids)
{
	int	*new_pids;
	int	len;
	int	i;

	len = pids_len(pids);
	new_pids = malloc(sizeof(int) * (len + 1));
	if (!new_pids)
	{
		ms->exit_code = 1;
		return (NULL);
	}
	i = -1;
	while (++i < len + 1)
		new_pids[i] = -1;
	if (!pids)
		return (new_pids);
	i = -1;
	while (pids[++i] != -1)
		new_pids[i] = pids[i];
	free(pids);
	return (new_pids);
}

void	wait_pids(t_ms *ms)
{
	int	status;
	int	i;

	if (ms->pids)
	{
		i = 0;
		set_interactive_mode(2);
		while (ms->pids[i] != -1)
		{
			waitpid(ms->pids[i++], &status, 0);
			if (WIFSIGNALED(status))
				ms->exit_code = WTERMSIG(status) + 128;
			else
				ms->exit_code = WEXITSTATUS(status);
			if (ms->exit_code == 130)
				g_sig = SIGINT;
		}
		set_interactive_mode(3);
		free(ms->pids);
		ms->pids = NULL;
	}
	if (ms->exit_code == 131)
		write(2, "Quit (core dumped)\n", 19);
}
