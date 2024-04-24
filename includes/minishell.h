/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:52:11 by bvasseur          #+#    #+#             */
/*   Updated: 2024/04/23 17:41:48 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <builts_in.h>
# include <errno.h>
# include <parser.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/resource.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>

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

typedef struct s_minishell
{
	char		*line;
	t_env		*env;
	char		*prompt;
	char		**envp;
	char		**char_env;
	t_node		*root_node;
	t_tokens	*tokens;
	int			*pids;
	int			heredoc_number;
	int			exit_code;
	int			error_occured;
	int			should_exit;
}				t_ms;

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
	int			should_execute;
}				t_execution;

typedef struct s_expand
{
	char		*mask;
	char		*name;
	char		*line;
	int			state;
	int			i;
	int			is_expand;
	int			is_wildcard;
}				t_expand;

typedef struct s_expand_args
{
	int			ign_qte;
	int			shld_ch_ifs;
	int			should_expand;
	int			expand_wc;
	int			expand_special_cases;
}				t_expand_args;

typedef struct s_perr
{
	t_ms		*ms;
	int			exit_code;
	int			n;
	int			bs;
}				t_perr;

/*========== ERRORS ==========*/

void			perr(t_perr perr, ...);
void			ft_free_ms(t_ms *ms);

/*========== SIGNALS ==========*/

void			set_interactive_mode(int set);

/*========== PROMPTS ==========*/

char			*get_prompt(t_env *env);
char			*add_colors(char *str, char *(*color_pattern)(int, int));
char			*moving_rainbow_pattern(int i, int len);
char			*moving_france_pattern(int i, int len);

/*========== WILDCARDS ==========*/

char			*wildcards(t_ms *ms, char *char_wc);
char			*symbol_to_char(t_tokens *token);
int				is_existing_dir(char *path);
int				is_evenly_quoted(char *str, int n);
t_wc			*ft_wcnew(t_symbol symbol, char *arg, t_wc *next);
t_wc			*ft_wclast(t_wc *stack);
void			ft_wcadd_back(t_wc **stack, t_wc *new);
bool			ft_wcnew_back(t_wc **tokens, t_symbol symbol, char *arg);
void			ft_wcclear(t_wc **stack);
void			quote_mask(char *wc, char *mask);
bool			mask_wc(t_wc *wc);
bool			get_files(t_tokens **files, DIR *directory, t_wc *wc);
void			sort_files(t_tokens *files);
char			*tokens_to_string(t_tokens *tokens);

/*========== EXPAND ==========*/

char			*place_wildcards(t_ms *ms, t_expand exp_var);
int				exp_len(t_env *env, char *line, t_expand_args args, int state);
int				special_cases_total_len(t_ms *ms, char *str,
					t_expand_args args);
int				check_quotes(char *str);
int				len_env_name(char *str);
t_expand		expand_var(t_ms *ms, char *str, t_expand_args args);
int				change_state(char *str, int state, char *shld_remove, int i);
int				expand_args(t_ms *ms, t_node *node, bool is_export);
int				expand_redirects(t_ms *ms, t_node *node);
void			expand_here_doc(t_ms *ms, t_tokens *token);
void			expand_tokens(t_ms *ms, t_node *node);
char			*remove_quotes(t_expand exp_var, t_expand_args args);

/*========== EXECUTION ==========*/

/*----- IFS -----*/

char			*change_ifs(char *str, char *should_remove);
int				should_split_ifs(char *str);
void			split_ifs(t_tokens **tokens, int is_wildcard, int is_expand);
t_tokens		*shift_tokens(t_tokens *tokens, t_tokens **tmp_tok);

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
int				transform_to_chars(t_ms *ms, t_node *node);
int				check_command(t_ms *ms, char **cmd);
void			execute_node(t_execution execution, t_node *node,
					t_symbol last_operator);
int				execute_built_ins(t_execution execution, t_node *node);
void			child(t_execution execution, t_node *node);
void			parent(t_execution execution);
void			unlink_here_docs(t_ms *ms);

/*----- FDS -----*/

void			close_all_fds(void);
void			try_close_fd(int fd);

/*----- UTILS -----*/

int				reset_envp(t_ms *ms);
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
