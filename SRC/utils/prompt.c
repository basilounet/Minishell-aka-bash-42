/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 13:45:27 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/02 17:02:36 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*moving_rainbow_pattern(int i, int len)
{
	static int	j = 0;

	if (i >= len - 1)
		j = (j + 1) % len;
	i = (i + j) % len;
	if (i <= len * 1 / 5)
		return (MAGENTA);
	else if (i <= len * 2 / 5)
		return (BLUE);
	else if (i <= len * 3 / 5)
		return (GREEN);
	else if (i <= len * 4 / 5)
		return (YELLOW);
	else if (i <= len)
		return (RED);
	return (BASE_COLOR);
}

char	*moving_france_pattern(int i, int len)
{
	static int	j = 0;

	if (i >= len - 1)
		j = (j + 1) % len;
	i = (i + j) % len;
	if (i <= len * 1 / 3)
		return (BLUE);
	else if (i <= len * 2 / 3)
		return (WHITE);
	else if (i <= len)
		return (RED);
	return (BASE_COLOR);
}

char	*add_colors(char *str, char *(*color_pattern)(int, int))
{
	char	*colored_str;
	int		len;
	int		i;

	i = -1;
	colored_str = NULL;
	len = ft_strlen(str);
	if (!str || !color_pattern)
		return (NULL);
	while (++i < len)
		colored_str = ft_str_reajoin(colored_str,
				ft_str_reajoin(color_pattern(i, len), ft_substr(str, i, 1), 0,
					1), 1, 1);
	colored_str = ft_str_reajoin(colored_str, BASE_COLOR, 1, 0);
	free(str);
	return (colored_str);
}

char	*get_prompt(t_env *env)
{
	char	*home;
	char	*pwd;
	char	*str;
	
	pwd = ft_strdup(ft_getenv(env, "PWD"));
	home = ft_getenv(env, "HOME");
	if (ft_getenv(env, "USER"))
		str = ft_str_reajoin(ft_getenv(env, "USER"),
				ft_strdup("@baseshell:"), 0, 1);
	else
		str = ft_strdup("USER@baseshell:");
	if (!pwd)
		pwd = getcwd(NULL, 0);
	if ((home && pwd && !ft_strncmp(home, pwd, ft_strlen(home)) && home[ft_strlen(home)] != '/')
				&& (pwd[ft_strlen(home)] == '/'
				|| pwd[ft_strlen(home)] == '\0'))
		str = ft_str_reajoin(str, ft_strjoin3("~", pwd + ft_strlen(home), "$ "),
				1, 1);
	else
		str = ft_str_reajoin(str, ft_strjoin(pwd, "$ "), 1, 1);
	if (pwd)
		free(pwd);
	return (str);
}
