/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 05:59:04 by msilva-c          #+#    #+#             */
/*   Updated: 2025/06/10 13:37:42 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../includes/minishell.h"

/* env */
char				**duplicate_envp(char **envp);
void				free_env(t_env *env);

/* envp_1 */
int					dup_var(t_env *start, t_env *new);
void				var_add_back(t_env *start, t_env *new);
t_env				*create_var(const char *str);
int					check_env(char **envp);

/* envp_2 */
char				**get_default_env(void);
t_env				*empty_env(void);
t_env				*env_dup(t_env *env);

/* init_exec */
int					count_cmds(void);
int					strlen_args(char **args);
char				**add_to_matrix(char *content, char **args);
t_exec				*init_exec(void);
int					set_exec(void);

/* init.c */
char				*get_home(void);
t_msh				*msh(void);
t_msh				*init_all(char **envp);
t_env				*init_env(char **envp);

/* parser1 */
int					parser(void);
int					set_in_and_out(t_command_table *cmd_table);
int					process_command(t_command_table **command_table);

/* parser2 */
int					ft_compare(char **split_line, int i);
t_simple_command	*initialize_simple_command(void);
void				check_expansions(void);

/* spaces */
void				double_quoted_string(const char *input, char *output,
						int *i, int *j);
void				single_quoted_string(const char *input, char *output,
						int *i, int *j);
void				handle_special_char(const char *input, char *output, int *i,
						int *j);
size_t				calculate_size(const char *input);
char				*add_spaces(char *in);
size_t				handle_double_special(const char *input, int *i);
size_t				handle_single_special(const char *input, int i);

/* splitter */
int					count_words2(const char *str);
char				*ft_substr2(const char *str, int start, int len);
char				**split_by_spaces(char *input);
char				*extract_next_token(const char *input, int *i);

/* matrix */
void				assign(const char *content, t_token *new_token);
t_token				*create_token(const char *content, int index);
void				add_token_to_list(t_token **head, t_token *new_token);
t_token				*matrix_to_tokens(char **matrix);

/* init commands */
t_simple_command	*init_simple_command(void);
t_redirs_list		*init_redirs_list_node(t_token **token);
t_simple_command	*initialize_simple_command(void);
t_command_table		*init_cmd_table(void);
void				add_redir(t_redirs_list **head, t_redirs_list *new_node);
void				add_cmd_info(t_simple_command **cmd, t_token *token);

/* parse_command 2 */
void				free_redirs_list(t_redirs_list *head);
void				free_command_structs(t_simple_command *cmds,
						int n_commands);

int					parser(void);
int					handle_parser(void);
void				free_simplecommand_and_table(t_command_table *cmd_table);
void				help_parser(t_command_table *command_table);
char				*parser_add_spaces(void);
char				**parser_split_line(char *new_line);
int					parser_tokens(char **split_line);
int					parser_syntax_and_expand(void);
int					parser_process_command(t_command_table **command_table);
void				cmd_table_add_back(t_command_table **table,
						t_command_table *new_node);

int					check_open_single_quotes(const char *str);
int					check_open_double_quotes(const char *str);
int					check_unclosed_quotes(char *str);
char				*extract_double_quoted(const char *input, int *i);
char				*extract_single_quoted(const char *input, int *i);
char				*extract_unquoted(const char *input, int *i);

int					handle_cmd_token(t_command_table *new_node, t_token *token,
						t_command_table **command_table);
int					handle_redir_token(t_command_table *new_node,
						t_token **tokens);
int					handle_pipe_token(t_command_table **command_table,
						t_command_table **new_node);
t_command_table		*create_cmd_table_node(void);

void				skip_double_quote(const char *str, int *i);
void				skip_single_quote(const char *str, int *i);

char				*her_delim_check(char *line, int check_len);

#endif
