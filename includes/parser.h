/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 05:59:04 by msilva-c          #+#    #+#             */
/*   Updated: 2025/05/20 14:15:09 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../includes/minishell.h"

/* env */
char				**duplicate_envp(char **envp);
void				free_env(char **env);

/* envp_1 */
int					dup_var(t_env *start, t_env *new);
void				var_add_back(t_env *start, t_env *new);
t_env				*create_var(char *str);
int					check_env(char **envp);

/* envp_2 */
char				**get_default_env(void);
t_env				*empty_env(void);
t_env				*env_dup(t_env *env);

/* init_exec */
int					count_cmds(void);
int					strlen_args(char **args);
char				**add_to_matrix(char *content, char **args);
void				tokens_to_exec(t_token *token, t_exec *exec, int nbr_cmds);
t_exec				*init_exec(void);
int					set_exec(void);

/* init.c */
char				*get_home(void);
t_msh				*msh(void);
t_msh				*init_all(char **envp);

/* parser.c */
int					parser(void);
void				set_in_and_out(t_command_table *cmd_table);
void				print_msh(t_msh *msh);

/* spaces */
void				double_quoted_string(const char *input, char *output,
						int *i, int *j);
void				single_quoted_string(const char *input, char *output,
						int *i, int *j);
void				handle_special_char(const char *input, char *output, int *i,
						int *j);
size_t				calculate_size(const char *input);
char				*add_spaces(char *input);

/* splitter */
int					count_words2(const char *str);
char				*ft_substr2(const char *str, int start, int len);
char				**split_by_spaces(char *input);

/* matrix */
void				assign(const char *content, t_token *new_token);
t_token				*create_token(const char *content, int index);
void				add_token_to_list(t_token **head, t_token *new_token);
t_token				*matrix_to_tokens(char **matrix);

/* init commands */
t_simple_command	*init_simple_command(void);
t_redirs_list		*init_redirs_list_node(t_token **token);
t_simple_command 	*initialize_simple_command(void);
t_command_table		*init_cmd_table(void);
void 				add_redir(t_redirs_list **head, t_redirs_list *new_node);
void    			add_cmd_info(t_simple_command **cmd, t_token *token);

/* parse_command 1 */
void				free_command_structs(t_simple_command *cmds,
						int n_commands);
t_simple_command	*split_commands_into_structs(char **tokens, int token_count,
						int *n_commands);

/* parse_command 2 */
void				parse_redirections(t_token *token, t_redirs_list **redirs);
void				free_redirs_list(t_redirs_list *head);

#endif
