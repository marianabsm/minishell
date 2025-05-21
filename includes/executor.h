/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 19:58:02 by marianamest       #+#    #+#             */
/*   Updated: 2025/05/21 13:30:48 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../includes/minishell.h"

/* new_exec */
int is_builtin(char *command);
int find_path(t_simple_command *cmd);
int execute_command(t_simple_command *cmd, char **env);
void handle_pipes_and_redirections(t_exec *exec);
int start_executing(t_exec *exec, t_command_table *cmd_table);

/* redirection_1 */
int exec_r(t_exec *ex, char *value);
int exec_rr(t_exec *ex, char *value);
char **exred(char **args, int i);
int size_args(char **args);

/* redirection_2 */
int exec_l(t_exec *ex, char *value);
int exec_red2(t_exec *ex, char *key, char *value);
char **exec_red(t_exec *ex, int ex_index);
int	check_redirs(t_exec *ex);

/* start_executer.c */
void    close_args_fds(t_exec *ex);

/* sys_call_error_1 */
char *get_path(t_env *env);
char *path_search(char *str, t_env *env);
int	pipe_error(void);
void	close_fds(int *fds);
int	fork_error(void);

/* sys_call_error_2 */
int ft_check_access(char *str, char *cmd, char **tmp);

#endif