/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:47:49 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/22 13:52:34 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int ac, char **av, char **env)
{
	t_ms	ms;
	char	*line;
	char	*str;

	(void)ac;
	(void)av;
	ms.env = ft_mapcpy(env, ft_maplen(env));
	ms.prompt = add_colors(get_prompt(&ms), &moving_rainbow_pattern);
	str = NULL;
	while (1)
	{
		line = readline(ms.prompt);
		add_history(line);
		str = expand_var(&ms, line, 0);
		ft_printf("%s\n", str);
		if (str)
			free(str);
		if (line)
			free(line);
		free(ms.prompt);
		ms.prompt = add_colors(get_prompt(&ms), &moving_rainbow_pattern);
	}
	free(ms.prompt);
	ft_free_map(ms.env, ft_maplen(ms.env));

}
