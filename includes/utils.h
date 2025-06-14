/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 06:01:56 by msilva-c          #+#    #+#             */
/*   Updated: 2025/06/10 22:52:04 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../includes/minishell.h"

/* free_1 */
void		free_var(t_env *var);
void		free_matrix(char **matrix);
void		free_tokens(t_token *tokens);
void		free_command_table(t_command_table *cmd_table);

/* free_2 */
void		free_and_exit(t_msh *m);

/* heredoc_utils */
void		int_to_str(int num, char *str);

/* libft_utils1 */
void		ft_swap(char **a, char **b);
void		ft_swap_char(char *a, char *b);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strchr(const char *s, int c);
void		ft_putstr_fd(char *s, int fd);

/* libft_utils2 */
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_strcpy(char *dest, char *src);
char		*ft_strncpy(char *dest, char *src, unsigned int n);
char		*ft_strcat(char *dest, const char *src);
char		*ft_strncat(char *dest, char *src, unsigned int nb);

/* libft_utils3 */
int			ft_isoperator(char *str, int i);
int			ft_isspace(char c);
int			ft_isalpha(char c);
int			ft_isdigit(char c);
int			ft_isquote(char c);

/* libft_utils4 */
char		**copy_matrix(char **src);
int			ft_atoi(char *str);
char		*ft_strjoin(const char *s1, const char *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t n);

/* libft_utils5 */
char		*ft_itoa(int n);
int			ft_counter(char const *str, char c);
char		**ft_split(char const *str, char c);
int			ft_intmin(char *str);
size_t		ft_digits(int n);

/* libft_utils6 */
char		*ft_strtrim(char *s, char c);
char		*ft_strncpy2(char *dest, const char *src, unsigned int n);
char		*ft_strjoin_free(char *s1, const char *s2);
char		*ft_struntil(char *s, char c);
char		*ft_strafter(const char *s, char c);
char		*ft_strjoin3(char *s1, char *s2, char *s3);

/* malloc */
void		*ft_memset(void *s, int c, size_t n);
void		*safe_malloc(size_t size);

/* utils_builtins */
void		print_error(void);
void		my_strcpy(char *dest, const char *src);
void		my_strcat(char *dest, const char *src);
int			ft_isalnum(int c);

/* utils_str */
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strlen(const char *str);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strdup(const char *s);
int			is_special_char(char c);

/* syntax_errors */
int			check_syntax_general(t_token *tokens);
void		reset_fds(void);
void		close_cmd_table_fds(t_command_table *cmd_table);
void		prep_next_cmdline(t_msh *m);
void		init_fds(void);
void		free_token_list(t_token *tokens);

long long	ft_strtoll(const char *str, char **endptr, int base);
int			ft_parse_sign(const char **s);
void		ft_skip_whitespace(const char **s);
int			ft_detect_base(const char **s, int base);
int			ft_isdigit_base(int c, int base);
int			ft_getdigit(int c);
int			ft_handle_overflow(int sign, long long *result);
int			find_substring_index(const char *haystack, const char *needle);
size_t		ft_strspn(const char *s, const char *accept);
size_t		ft_strlen3(const char *str);

#endif
