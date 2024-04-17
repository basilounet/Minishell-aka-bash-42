/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:51:20 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/16 13:42:46 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*change_ifs(char *str, char *should_remove)
{
	char	*ifs;
	int		state;
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
			state = change_state(str + i, state, NULL, i);
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
	if (str[0] == 0)
		return (1);
	while (str[i])
	{
		state = change_state(str + i, state, NULL, i);
		if (state == 0 && str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

t_tokens	*shift_tokens(t_tokens **tokens)
{
	t_tokens	*prev;
	t_tokens	*next;
	t_tokens	*tmp_tok;

	tmp_tok = *tokens;
	free(tmp_tok->arg);
	while (tmp_tok->next)
	{
		prev = tmp_tok;
		next = tmp_tok->next;
		tmp_tok->arg = next->arg;
		tmp_tok->next = NULL;
		tmp_tok = next;
		if (tmp_tok->next)
			prev->next = tmp_tok;
	}
	free(tmp_tok);
	prev->next = NULL;
	tmp_tok = NULL;
	return (*tokens);
}

t_tokens	*split_ifs(t_tokens **tokens)
{
	t_tokens	*tok_list;
	t_tokens	*tok_last;
	char		**split;
	int			i;

	if (ft_countc((*tokens)->arg, -1) == 0)
		return (*tokens);
	split = ft_split((*tokens)->arg, -1);
	if (!split)
		return (*tokens);
	free((*tokens)->arg);
	if (!split[0])
	{
		free(split);
		(*tokens)->arg = NULL;
		return (*tokens);
	}
	(*tokens)->arg = split[0];
	tok_list = NULL;
	i = 0;
	while (split[++i])
		ft_tokadd_back(&tok_list, ft_toknew(0, split[i], NULL));
	free(split);
	tok_last = ft_toklast(tok_list);
	tok_last->next = (*tokens)->next;
	(*tokens)->next = tok_list;
	return (tok_last);
}
