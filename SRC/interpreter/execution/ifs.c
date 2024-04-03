/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:51:20 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/03 13:00:02 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*change_ifs(char *str, char *should_remove)
{
	char	*ifs;
    int     state;
	int		i;
	int		j;

	i = -1;
	ifs = " \t\n";
    state = 0;
	if (!str || !should_remove)
		return (NULL);
	while (str[++i])
	{
		j = 0;
		if (should_remove[i] == 'y')
	        state = change_state(str[i], state, NULL, i);
		while (state == 0 && ifs[j])
			if (str[i] == ifs[j++])
				str[i] = -1;
	}
	return (str);
}

int	should_split_ifs(char *str)
{
	int	state;
	int	i;

	i = 0;
	state = 0;
	while (str[i])
	{
		state = change_state(str[i], state, NULL, i);
		if (state == 0 && str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

void	split_ifs(t_tokens **tokens)
{
	t_tokens	*tok_list;
	t_tokens	*tok_last;
	char		**split;
	int			i;

	if (ft_countc((*tokens)->arg, -1) == 0)
		return ;
	split = ft_split((*tokens)->arg, -1);
	if (!split)
		return ;
	free((*tokens)->arg);
	(*tokens)->arg = split[0];
	tok_list = NULL;
	i = 0;
	while (split[++i])
	{
		ft_tokadd_back(&tok_list, ft_toknew(0, NULL));
		ft_toklast(tok_list)->arg = split[i];
	}
	free(split);
	tok_last = ft_toklast(tok_list);
	tok_last->next = (*tokens)->next;
	(*tokens)->next = tok_list;
	(*tokens) = tok_last;
}
