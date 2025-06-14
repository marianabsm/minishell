/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 19:58:02 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 20:20:49 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../includes/minishell.h"

/* new_exec */
int		find_path(t_simple_command *cmd);
int		execute_command(t_simple_command *cmd, char **env);
int		start_executing(t_exec *exec, t_command_table *cmd_table);
void	close_all_fds_except(int in_fd, int out_fd);
void	close_pipes(t_exec *exec);
void	close_in_exec(t_exec *exec);
char	**skip_empty_args(char **args);
int		pre_exec_parse(t_command_table *current_cmd);
int		pipe_problem(t_exec *exec, t_command_table *current_cmd);
int		built_in_start(t_command_table *current_cmd);
int		cmd_loop(t_exec *exec, t_command_table *current_cmd, int last_status);
void	child_p(t_exec *exec, t_command_table *current_cmd);
void	daddy_p(t_exec *exec, t_command_table *current_cmd);
void	msh_loop(char **envp);

/* exec_builtins */
void	execute_builtins(t_simple_command *cmd);
int		is_builtin(char *command);

/* redirection_1 */
int		exec_r(t_exec *ex, char *value);
int		exec_rr(t_exec *ex, char *value);
char	**exred(char **args, int i);
int		size_args(char **args);

/* redirection_2 */
int		exec_l(t_exec *ex, char *value);
int		exec_red2(t_exec *ex, char *key, char *value);
void	start_execution(t_exec *ex, int index);

/* sys_call_error_1 */
char	*get_path(t_env *env);
char	*path_search(char *str, t_env *env);
int		pipe_error(void);
void	close_fds(int *fds);
int		fork_error(void);

/* sys_call_error_2 */
int		ft_check_access(char *str, char *cmd, char **tmp);

void	cmd_permiss_errors(t_simple_command *cmd);
void	decide_fd(t_simple_command *cmd);
void	is_a_dir(const char *exec_path);
void	perm_den(const char *fail_path);
void	child_process(t_simple_command *cmd, char **env);
int		parent_process(t_simple_command *cmd, pid_t pid, int status);
void	handle_execve_error(t_simple_command *cmd);
void	handle_permission_and_not_found(const char *fail_path);
void	not_found2(const char *fail_path);
void	not_found1(t_simple_command *cmd);
void	check_ls(t_simple_command *cmd);

#endif