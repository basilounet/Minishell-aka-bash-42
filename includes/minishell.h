/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:52:11 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/09 17:18:26 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <builts_in.h>
# include <libft.h>
# include <parser.h>
# include <pipex.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <signal.h>
# include <termios.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>

# define BASE_COLOR "\001\033[0;39m\002"
# define GRAY "\001\033[0;90m\002"
# define RED "\001\033[0;91m\002"
# define GREEN "\001\033[0;92m\002"
# define YELLOW "\001\033[0;93m\002"
# define BLUE "\001\033[0;94m\002"
# define MAGENTA "\001\033[0;95m\002"
# define CYAN "\001\033[0;96m\002"
# define WHITE "\001\033[0;97m\002"
# define SYN_ERR "syntax error near unexpected token "

extern int	g_sig;

typedef struct s_minishell
{
	t_env	*env;
	char	*prompt;
	int		exit_code;
	int		heredoc_number;
	t_node	*root_node;
	char	**envp;
	int		*pids;
}			t_ms;

typedef struct s_execution
{
	t_ms	*ms;
	int		left_pipe[2];
	int		right_pipe[2];
	int		input;
	int		output;
	int		is_in_pipe;
}			t_execution;

typedef struct s_expand
{
	char	*qte;
	char	*name;
	char	*line;
	int		state;
	int		i;
}			t_expand;

typedef struct s_expand_args
{
	int		ign_qte;
	int		shld_ch_ifs;
	int		should_expand;
}			t_expand_args;

char	*tokens_to_string(t_tokens *tokens);
char		*ft_getenv(t_env *env, char *to_get);
int	is_existing_dir(char *path);
int perr(int exit_code, int n, int bs, ...);
char					*symbol_to_char(t_tokens *token);

/*========== PROMPTS ==========*/

char		*get_prompt(t_env *env);
char		*add_colors(char *str, char *(*color_pattern)(int, int));
char		*moving_rainbow_pattern(int i, int len);
char		*moving_france_pattern(int i, int len);

/*========== BUILTS-IN ==========*/

int			is_built_in(char *command);
void		env(t_env *env);
void		pwd(void);
int			cd(t_env **env, char **args);

/*========== EXPAND ==========*/

int			check_quotes(char *str);
int			len_env_name(char *str);
char		*expand_var(t_env *env, char *str, t_expand_args args);
int			change_state(char *str, int state, char *shld_remove, int i);
void		expand_args(t_ms *ms, t_node *node);
void		expand_redirects(t_ms *ms, t_node *node);

/*========== EXECUTION ==========*/

char		*change_ifs(char *str, char *should_remove);
int			should_split_ifs(char *str);
void		split_ifs(t_tokens **tokens);

void		prepare_and_execute(t_ms *ms, t_node *node);
void		expand_tokens(t_ms *ms, t_node *node);
void	execute_node(t_execution execution, t_node *node);
void		update_inputs(t_node *node);
void		update_outputs(t_node *node);
void		add_redirect_node(t_node *node, t_tokens *token);
void		open_all_outputs(t_ms *ms, t_node *node);
void		unlink_here_docs(t_ms *ms);
void	transform_to_chars(t_node *node);
void	check_command(t_ms *ms, char **cmd);
void	expand_here_doc(t_ms *ms, char *name);
int	execute_built_ins(t_execution execution, t_node *node);

void wait_pids(t_ms *ms);
int	*add_pid_space(t_ms *ms, int *pids);
int pids_len(int *pids);
void	print_pid(int *pids);


void	child(t_execution execution, t_node *node);
void	parent(t_execution execution);
void		try_close_fd(int fd);

/*========== EXECUTION_UTILS ==========*/

void	reset_envp(t_ms *ms);

int			has_input(t_tokens *tokens);
int			has_output(t_tokens *tokens);
t_tokens	*get_input_tok(t_tokens *tokens);
t_tokens	*get_output_tok(t_tokens *tokens);
int			is_append(t_command *cmd);
int	get_input_fd(t_ms *ms, t_tokens *tokens);
int	get_output_fd(t_tokens *tokens);

void		print_node(t_node *node, int depth);
void		print_tokens(t_tokens *tokens, int depth);
int			ft_envsize(t_env *env);
#endif
