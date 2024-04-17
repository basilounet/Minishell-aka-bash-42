/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts_in.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:33:23 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/16 13:33:25 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTS_IN_H
# define BUILTS_IN_H

# include <dirent.h>
# include <sys/stat.h>

typedef struct s_env
{
	char			*name;
	char			*var;
	struct s_env	*next;
}					t_env;

/*========== CD ==========*/

int					cd(t_env **env, char **args);
int					cd_set_pwd(t_env **env);
char				*check_cdpath(t_env **env, char *directory);

/*========== EXPORT ==========*/

int					print_export(t_env *env);
int					export(t_env **env, char **args);

/*========== ECHO ==========*/

void				echo(char **args);

/*========== ENV ==========*/

void				env(t_env *env);
char				*ft_getenv(t_env *env, char *to_get);
t_env				*ft_envnew(char *name, char *var, t_env *next);
t_env				*ft_envlast(t_env *stack);
char				*get_env_var(t_env *env, char *name);
void				ft_envdel_one(t_env *stack);
void				ft_envadd_back(t_env **stack, t_env *new);
void				ft_envclear(t_env *stack);
char				**env_list_to_array(t_env *env);
int					env_array_to_list(t_env **env, char **char_env);
int					ft_envsize(t_env *env);

/*========== PWD ==========*/

void				pwd(void);

/*========== UNSET ==========*/

void				unset(t_env **env, char **args);
void				unset_name(t_env **env, char *name);

/*========== EXIT ==========*/

int					ft_exit(t_ms *ms, char **args);

/*========== UTILS ==========*/

int					is_built_in(char *command);

#endif