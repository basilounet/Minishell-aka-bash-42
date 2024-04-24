/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:51:20 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/23 16:42:08 by bvasseur         ###   ########.fr       */
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

t_tokens	*shift_tokens(t_tokens *tokens, t_tokens **tmp_tok)
{
	t_tokens	*first;
	t_tokens	*previous;
	t_tokens	*next;

	if (!tokens)
		return (NULL);
	first = tokens;
	previous = NULL;
	while (tokens)
	{
		if (tokens->arg[0] == 0 && tokens->symbol == T_EXPAND)
		{
			next = tokens->next;
			if (first == tokens)
				first = next;
			ft_free_ptr(2, tokens->arg, tokens);
			if (previous)
				previous->next = next;
			*tmp_tok = next;
			return (first);
		}
		previous = tokens;
		tokens = tokens->next;
	}
	return (first);
}

static void	add_ifs(char **split, t_tokens **tokens, int is_wildcard,
		int is_expand)
{
	t_tokens	*tok_list;
	t_tokens	*tok_last;
	int			i;

	tok_list = NULL;
	tok_last = NULL;
	i = 0;
	while (split[++i])
	{
		if (is_expand)
			ft_tokadd_back(&tok_list, ft_toknew(T_EXPAND, split[i], NULL));
		else if (is_wildcard)
			ft_tokadd_back(&tok_list, ft_toknew(T_WILDCARD, split[i], NULL));
		else
			ft_tokadd_back(&tok_list, ft_toknew(T_ARG, split[i], NULL));
	}
	free(split);
	if (i != 1)
	{
		tok_last = ft_toklast(tok_list);
		tok_last->next = (*tokens)->next;
		(*tokens)->next = tok_list;
	}
}

void	split_ifs(t_tokens **tokens, int is_wildcard, int is_expand)
{
	char	**split;

	if (ft_countc((*tokens)->arg, -1) == 0)
		return ;
	split = ft_split((*tokens)->arg, -1);
	if (!split)
		return ;
	free((*tokens)->arg);
	if (!split[0])
	{
		free(split);
		(*tokens)->arg = NULL;
		return ;
	}
	(*tokens)->arg = split[0];
	if (is_wildcard)
		(*tokens)->symbol = T_WILDCARD;
	add_ifs(split, tokens, is_wildcard, is_expand);
}
