/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts_in.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:33:23 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/24 14:57:23 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTS_IN_H
# define BUILTS_IN_H

# include <dirent.h>
# include <lexer.h>
# include <libft.h>
# include <sys/stat.h>

typedef struct s_minishell	t_ms;

typedef struct s_env
{
	char					*name;
	char					*var;
	struct s_env			*next;
}							t_env;

typedef struct s_wc
{
	t_symbol				symbol;
	char					*wc;
	char					*mask;
	struct s_wc				*next;
	t_ms					*ms;
}							t_wc;

typedef struct s_minishell	t_ms;

/*========== CD ==========*/

int							cd(t_ms *ms, t_env **env, char **args);
int							cd_set_pwd(t_env **env, t_ms *ms);
char						*check_cdpath(t_env **env, char *directory);

/*========== ECHO ==========*/

void						echo(t_ms *ms, char **args);

/*======= ENV / EXPORT =======*/

int							print_export(t_env *env);
int							export(t_ms *ms, t_env **env, char **args);
void						replace_env(t_env **env, t_env *new);

void						env(t_ms *ms, t_env *env, char **args);
char						*ft_getenv(t_env *env, char *to_get);
t_env						*ft_envnew(char *name, char *var, t_env *next);
t_env						*ft_envlast(t_env *stack);
char						*get_env_var(t_env *env, char *name);
void						ft_envdel_one(t_env *stack);
void						ft_envadd_back(t_env **stack, t_env *new);
void						ft_envclear(t_env *stack);
char						**env_list_to_array(t_env *env);
int							env_array_to_list(t_env **env, char **char_env);
int							ft_envsize(t_env *env);
t_env						*parse_char_env(t_env *env, char *char_env, int j,
								int append);

/*========== PWD ==========*/

void						pwd(t_ms *ms);

/*========== UNSET ==========*/

void						unset(t_ms *ms, t_env **env, char **args);
t_env						*unset_name(t_env *env, char *name);

/*========== EXIT ==========*/

int							ft_exit(t_ms *ms, char **args, int is_in_pipe);

/*========== UTILS ==========*/

int							is_built_in(char *command);

#endif