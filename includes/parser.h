/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 05:59:04 by msilva-c          #+#    #+#             */
/*   Updated: 2025/03/31 19:03:53 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../includes/minishell.h"

/* create_token.c */
int			get_type(char *str);
void		token_add_back(t_token *head, t_token *new);
t_token		*init_token(char *str);
t_token		*create_tokens(char **temp);

/* envp_1.c */
int			dup_var(t_env *start, t_env *new);
void		var_add_back(t_env *start, t_env *new);
t_env		*create_var(char *str);
int			check_env(char **envp);
t_env		*get_env(char **envp);

/* envp_2.c */
char		**get_default_env(void);
t_env		*empty_env(void);
t_env		*_dup(t_env *env);

/* init_exec.c */
int			count_cmds(t_token *tokens);
int			strlen_args(char **args);
// not being used: char    **add_prefix(t_token *token, char **args);
char		**add_to_matrix(char *content, char **args);
void		tokens_to_exec(t_token *token, t_exec *exec, int nbr_cmds);
t_exec		*init_exec(t_token *tokens);
int			set_exec(void);

/* init.c */
char		*get_home(void);
t_msh		*msh(void);
t_msh		*init_all(char **envp);

/* parser.c */
int			parser(void);
void		print_msh(t_msh *msh);

/* quotes.c */
int			in_quotes(char *line, int max);
int			in_singles(char *line, int max);
int			check_quotes(char *line);
int			skip_quotes(char *str, int i);

/* retokenizer.c */
t_token		*get_operator(t_token *t);
t_token		*get_word(t_token *t);
int			needs_retoken(char *cmd);
t_token		*get_which(t_token *old);
t_token		*update_token(t_token *old);
void		re_token(t_token *head);

/* split_spaces.c */
int			count_words(char *line);
int			parser_wdlen(char *line, int i);
char		**split_spaces(char *line);

/* syntax.c */
int			syntax_red(t_token *token);
int			syntax_pipe(t_token *token);
int			error_redir(t_token *token);
int			error_pipe(void);
int			check_syntax(t_token *token);

/* tokenizer.c */
int			tokenizer(void);

/* rm_quotes1.c */
char		*rm_quote(char *str);
void		rm_quotes_exec(void);
int			rm_strlen(char *str);

/* spaces */
void		double_quoted_string(const char *input, char *output, int *i, int *j);
void		single_quoted_string(const char *input, char *output, int *i, int *j);
void		handle_special_char(const char *input, char *output, int *i, int *j);
size_t		calculate_size(const char *input);
char		*add_spaces(const char *input);

/* splitter */
int			count_words2(const char *str);
char		*ft_substr2(const char *str, int start, int len);
static char	*extract_next_token(const char *input, int *i);
char		**split_by_spaces(const char *input);

/* matrix */
void assign(const char *content, t_token *new_token);
t_token *create_token(const char *content, int index);
void add_token_to_list(t_token **head, t_token *new_token);
t_token *matrix_to_tokens(char **matrix);

#endif
