/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:48:36 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/14 14:56:28 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define READ 0
# define WRITE 1

# include <libft.h>
# include "sys/wait.h"

enum		e_errors
{
	MALLOC_ERROR = 1,
	INVALID_AC_AMOUNT = 2,
	PATH_NOT_FOUND = 3,
	FILE_ERROR = 4,
	FORK_ERROR = 5,
	ENV_ERROR = 6
};

typedef struct s_px
{
	char	**env;
	char	***cmd;
	pid_t	*pid;
	int		index;
	int		total_cmd;
	int		is_append;
}			t_px;

/*========== ERRORS ==========*/

void		error(t_px *px, enum e_errors name);
void		pipe_func_error(t_px *px, int input_fd[2], int output_fd[2],
				int original_files[2]);

/*========== UNLEAK ==========*/

void		unleak(t_px *px);

/*========== STRUCT_INIT ==========*/

void		init_px(t_px *px);

/*========== STRUCT_INIT ==========*/

t_px		parse(int ac, char **av, char **env);
void		create_inputs(int ac, char **av, t_px *px, int input_files[2]);

/*========== PIPES ==========*/

int			pipex(int ac, char **av, char **env, int is_append);
void		sole_pipe(t_px *px, int input_files[2]);
void		first_pipe(t_px *px, int input_files[2], int new_pipe[2]);
void		last_pipe(t_px *px, int input_files[2], int new_pipe[2]);
void		all_pipes(t_px *px, int input_files[2]);
void		try_close_fd(int fd);

/*========== FORKS ==========*/

void		pipex_child(t_px *px, int input_fd[2], int output_fd[2],
				int original_fd[2]);
void		pipex_parent(t_px *px, int old_pipe[2], int new_pipe[2]);

/*========== HERE_DOCS ==========*/


void		here_doc(int ac, char **av, char **env, int is_append);

#endif
