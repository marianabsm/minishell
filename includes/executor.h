/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 19:58:02 by marianamest       #+#    #+#             */
/*   Updated: 2025/03/22 10:06:24 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../includes/minishell.h"

void ft_close(int fd);
int exec_r(t_exec *ex, char *value);
int exec_rr(t_exec *ex, char *value);
int exec_l(t_exec *ex, char *value);
int	check_redirs(t_exec *ex);
char **exred(char **args, int i);
int size_args(char **args);
void ft_close(int fd);
int ft_check_access(char *str, char *cmd, char **tmp);


/* src/executor/execute_builtins.c */
int     execute_builtin(t_exec *exec);
void    execute_builtin_in_fork(void); // Adjust parameters as needed
int     is_builtin(char *command);

/* fork_and_execute1.c */
void    handle_error(const char *message);
void    redirect_input(t_exec *exec);
void    redirect_output(t_exec *exec);
void    fork_and_execute_command(char **args, t_exec *exec, char **env);

/* fork_and_execute2.c */
void    setup_pipe_and_execute(t_exec *exec, int *input_fd, char **env);
void    wait_for_children(t_exec *exec);
void    execute_multiple_pipes(t_exec *exec, char **env);

/* redirections1.c */
void    handle_input_redirection(char **args, int *in_fd, int i);
void    handle_output_redirection(char **args, int *out_fd, int i);
void    handle_append_redirection(char **args, int *out_fd, int i);
void    handle_redirections(char **args, int *in_fd, int *out_fd);
void    execute_command(char **args, t_exec *exec, char **env);

/* redirections2.c */
void    child_process_logic(char **args, char **env);
void    execute_with_redirections(char **args, char **env);
void    handle_child_exit_status(int status);


/* start_executer.c */
void    close_args_fds(t_exec *ex);
int     fix_fd_pipe(t_exec *ex);
int     do_child(t_exec *exec);
void    new_child(t_exec *ex);
void    exec_single_cmd(t_exec *ex, int in, int out);
void    start_executing(void);

/* sys_call_error.c */
int     pipe_error(void);
void    close_fds(int *fds);
int     fork_error(void);

#endif
