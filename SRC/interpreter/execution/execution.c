/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:18:03 by bvasseur          #+#    #+#             */
/*   Updated: 2024/03/22 17:49:23 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <pipex.h>
#include <parser.h>

char    *get_input_name(t_tokens *tokens)
{
    t_tokens    *tmp;

    tmp = tokens;
    while (tmp && tmp->symbol != T_INPUT)
        tmp = tmp->next;
    if (!tmp || tmp->symbol != T_INPUT)
        return ("STDIN");
    return (tmp->arg);
}

char    *get_output_name(t_tokens *tokens)
{
    t_tokens    *tmp;

    tmp = tokens;
    while (tmp && tmp->symbol != T_OUTPUT)
        tmp = tmp->next;
    if (!tmp || tmp->symbol != T_OUTPUT)
        return ("STDOUT");
    return (tmp->arg);
}

int is_append(t_command *cmd)
{
    t_tokens    *tmp;

    tmp = cmd->redirects;
    while (tmp && tmp->symbol != T_APPEND)
        tmp = tmp->next;
    if (tmp && tmp->symbol == T_APPEND)
        return (1);    
    return (0);
}

void    execute_command(t_ms *ms, t_command *cmd)
{
    t_tokens    *tmp;
    char        **av;
    int         i;

    i = 1;
    tmp = cmd->args;
    av = ft_calloc(sizeof(char *), ft_toksize(cmd->args) + 3);
    if (!av)
        return ;
    av[0] = ft_strdup(get_input_name(cmd->redirects));
    while (tmp)
    {
        av[i++] = ft_strdup(tmp->arg);
        tmp = tmp->next;
    }
    av[i] = ft_strdup(get_output_name(cmd->redirects));
    ft_print_map(av);
    pipex(ft_toksize(cmd->args) + 2, av, ms->env, is_append(cmd));
}

void    execute_tree(t_ms *ms, t_tree *tree)
{
    (void)ms;
    (void)tree;
}

void    execute_all_commands(t_ms *ms, t_node *node)
{
    (void)ms;
    if (node->type == T_CMD)
        execute_command(ms, &node->cmd);
    else
        execute_tree(ms, &node->tree);
}   
