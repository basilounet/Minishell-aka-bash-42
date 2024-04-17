/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:52:11 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/16 18:18:17 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <parser.h>
# include <builts_in.h>
# include <errno.h>
//# include <libft.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
//# include <stdbool.h>
//# include <stdio.h>
# include <string.h>
# include <sys/resource.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/ioctl.h>

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
# define WRITE 1
# define READ 0

# ifndef DEBUG
#  define DEBUG 0
# endif

extern int		g_sig;

/*
 * minishell main structure
 * contains :
 * line
 * env
 * prompt
 * envp
 * char_env
 * tokens
 * pids
 * heredoc_numbers
 * exit_code
 */
typedef struct s_minishell
{
	char		*line;
	t_env		*env;
	char		*prompt;
	char		**envp;
	char		**char_env;
	t_tokens	*tokens;
	int			*pids;
	int			heredoc_number;
	int			exit_code;
}				t_ms;

/*
 * minishell execution structure
 * contains :
 * minishell structure
 * lower_pipe
 * left_pipe
 * right_pipe
 * upper_pipe
 * input
 * output
 * is_in_pipe
 */
typedef struct s_execution
{
	t_ms		*ms;
	int			lower_pipe[2];
	int			left_pipe[2];
	int			right_pipe[2];
	int			upper_pipe[2];
	int			input;
	int			output;
	int			is_in_pipe;
}				t_execution;

typedef struct s_expand
{
	char		*mask;
	char		*name;
	char		*line;
	int			state;
	int			i;
}				t_expand;

typedef struct s_expand_args
{
	int			ign_qte;
	int			shld_ch_ifs;
	int			should_expand;
	int			expand_wc;
	int			expand_special_cases;
}				t_expand_args;

char			*tokens_to_string(t_tokens *tokens);

/*========== ERRORS ==========*/

int				perr(int exit_code, int n, int bs, ...);

/*========== SIGNALS ==========*/

void			set_interactive_mode(int set);

/*========== PROMPTS ==========*/

char			*get_prompt(t_env *env);
char			*add_colors(char *str, char *(*color_pattern)(int, int));
char			*moving_rainbow_pattern(int i, int len);
char			*moving_france_pattern(int i, int len);

/*========== WILDCARDS ==========*/

char    		*wildcards(char *char_wc);
char			*symbol_to_char(t_tokens *token);
int				is_existing_dir(char *path);
int				is_evenly_quoted(char *str, int n);

/*========== EXPAND ==========*/

int				exp_len(t_env *env, char *line, t_expand_args args, int state);
int				special_cases_total_len(t_ms *ms, char *str,
					t_expand_args args);
int				check_quotes(char *str);
int				len_env_name(char *str);
char			*expand_var(t_ms *ms, char *str, t_expand_args args);
int				change_state(char *str, int state, char *shld_remove, int i);
void			expand_args(t_ms *ms, t_node *node);
int				expand_redirects(t_ms *ms, t_node *node);
void			expand_here_doc(t_ms *ms, t_tokens *token);
void			expand_tokens(t_ms *ms, t_node *node);

/*========== EXECUTION ==========*/

/*----- IFS -----*/

char			*change_ifs(char *str, char *should_remove);
int				should_split_ifs(char *str);
t_tokens		*split_ifs(t_tokens **tokens);
t_tokens		*shift_tokens(t_tokens **tokens);

/*----- PIDS -----*/

void			print_pid(int *pids);
int				pids_len(int *pids);
int				*add_pid_space(t_ms *ms, int *pids);
void			wait_pids(t_ms *ms);

/*----- REDIRECTIONS -----*/

void			update_inputs(t_node *node);
void			update_outputs(t_node *node);
void			add_redirect_node(t_node *node, t_tokens *token);
int				check_input(t_ms *ms, t_tokens *token);

/*----- EXECUTION -----*/

void			prepare_and_execute(t_ms *ms, t_node *node);
void			transform_to_chars(t_ms *ms, t_node *node);
void			check_command(t_ms *ms, char **cmd);
void			execute_node(t_execution execution, t_node *node,
					t_symbol last_operator);
int				execute_built_ins(t_execution execution, t_node *node);
void			child(t_execution execution, t_node *node);
void			parent(t_execution execution);
void			unlink_here_docs(t_ms *ms);
void			try_close_fd(int fd);

/*----- UTILS -----*/

void			reset_envp(t_ms *ms);
int				has_input(t_tokens *tokens);
t_tokens		*get_input_tok(t_tokens *tokens);
t_tokens		*get_output_tok(t_tokens *tokens);
int				get_input_fd(t_tokens *tokens);
int				get_output_fd(t_tokens *tokens);
char			*ft_substrc(char *str, int start, int end);

/*========== PRINT_NODE ==========*/

void			print_node(t_node *node, int depth);
void			print_tokens(t_tokens *tokens, int depth);

#endif
