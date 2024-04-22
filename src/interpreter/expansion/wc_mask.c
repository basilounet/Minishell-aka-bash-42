/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangouil <gangouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:03:33 by gangouil          #+#    #+#             */
/*   Updated: 2024/04/19 19:03:34 by gangouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builts_in.h>
#include <minishell.h>

void	quote_mask(char *wc, char *mask)
{
	int		i;
	bool	squote;
	bool	dquote;

	i = 0;
	squote = false;
	dquote = false;
	while (wc[i])
	{
		mask[i] = '0';
		if (!squote && wc[i] == '\"')
		{
			dquote = !dquote;
			mask[i] = '1';
		}
		else if (!dquote && wc[i] == '\'')
		{
			squote = !squote;
			mask[i] = '1';
		}
		else if (dquote || squote)
			mask[i] = '2';
		i++;
	}
}

bool	mask_wc(t_wc *wc)
{
	while (wc)
	{
		if (wc->symbol == T_ARG)
		{
			wc->mask = ft_calloc(ft_strlen(wc->wc) + 1, 1);
			if (!wc->mask)
				return (false);
			quote_mask(wc->wc, wc->mask);
		}
		wc = wc->next;
	}
	return (true);
}
