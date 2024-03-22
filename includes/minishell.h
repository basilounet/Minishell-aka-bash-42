/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:52:11 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/22 13:19:55 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <libft.h>
# include <pipex.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>

# define BASE_COLOR "\001\033[0;39m\002"
# define GRAY "\001\033[0;90m\002"
# define RED "\001\033[0;91m\002"
# define GREEN "\001\033[0;92m\002"
# define YELLOW "\001\033[0;93m\002"
# define BLUE "\001\033[0;94m\002"
# define MAGENTA "\001\033[0;95m\002"
# define CYAN "\001\033[0;96m\002"
# define WHITE "\001\033[0;97m\002"

typedef struct s_minishell
{
	char	**env;
	char	*prompt;
}			t_ms;

char		*ft_getenv(char **env, char *to_get);

/*========== PROMPTS ==========*/

char		*get_prompt(t_ms *ms);
char		*add_colors(char *str, char *(*color_pattern)(int, int));
char		*moving_rainbow_pattern(int i, int len);
char		*moving_france_pattern(int i, int len);

/*========== BUILDS-IN ==========*/

void		print_env(t_ms *ms);
void		cd(char *path);
void		pwd(void);

/*========== EXPAND ==========*/

int			check_quotes(char *str);
int			len_env_name(char *str);
char		*expand_var(t_ms *ms, char *original, int state);

#endif