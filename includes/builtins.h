/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 06:01:00 by msilva-c          #+#    #+#             */
/*   Updated: 2025/06/10 01:14:33 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../includes/minishell.h"

/* cd */
void	select_builtin(t_simple_command *cmd);
void	cd(char **args);

/* echo */
int		is_flag_n(char *str);
void	run_echo(char **args, int fd);
void	print_args(char **args, int start_index, int fd);

/* env1 */
char	*create_env_entry(const char *key, const char *value);
char	**allocate_env(char **envp);
int		process_env_variable(char *env_var, char **env, int i);
void	bi_env(t_simple_command *cmd);

/* env2 */
int		find_env_key_index(char **env, const char *key);
char	**update_env_var(char *arg, char **env, int idx);
char	**expand_env(char **env, char *new_entry);
void	set_or_add_env_value(char **env, const char *key, const char *value);

/* exit */
int		exit_format_error(char *cmd);
int		normalize_exit_code(int code);
void	exit_error(char *arg);
void	exec_exit(char **args);

/* export1 */
int		is_valid_var_char(char c, int is_first_char);
int		parse_export(char *str);
void	format_export_var(const char *var, int fd);
int		find_var_index(char **env, const char *var, int name_len);
void	add_new_var(char **env, const char *var);
void	update_env_global(void);

/* export2 */
char	**get_matrix_env(t_env *env);
void	print_sorted_env(t_env *env, int fd);
void	export_command(char **args, t_env *env, int fd);
char	**update_env_matrix(t_env *env_list);
int		get_env_list_size(t_env *env_list);

/* pwd */
void	pwd(int fd);

/* unset1 */
void	exec_unset(char **envp);
void	remove_var(char *name);
int		if_var_exists(char *name);

char	**add_to_env(char **env, char *new_var);
void	change_dir(char **args);
void	cd_home(char *home);
void	getcwd_error(void);
int		count_args(char **args);
void	set_env(char *key, char *value);

#endif
