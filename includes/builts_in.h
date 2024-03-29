/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts-in.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangouil <gangouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:17:23 by gangouil          #+#    #+#             */
/*   Updated: 2024/03/23 14:17:26 by gangouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTS_IN_H
# define BUILTS_IN_H

typedef struct s_env
{
    char            *name;
    char            *var;
    struct s_env    *next;
}   t_env;

int	print_export(t_env *env);
int	is_evenly_quoted(char *str, int n);
int	env_array_to_list(t_env **env, char **char_env);
int	    export(t_env **env, char **args);
t_env	*ft_envnew(char *name, char *var, t_env *next);
t_env	*ft_envlast(t_env *stack);
char	*get_env_var(t_env *env, char *name);
void	ft_envdel_one(t_env	*stack);
void    unset(t_env **env, char **args);
void	unset_name(t_env **env, char *name);
void	ft_envadd_back(t_env **stack, t_env *new);
void	ft_envclear(t_env *stack);

#endif