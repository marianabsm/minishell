/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 01:39:20 by msilva-c          #+#    #+#             */
/*   Updated: 2025/06/09 13:30:49 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../includes/minishell.h"

/* expand1 */
int		find_and_size_var_name(char *input);
char	*find_var_name2(char *input, int size_of_var_name);
char	*delete_number_and_dollar_sign(char *input, int dollar_index);
char	*delete_dollar_sign(char *input, int dollar_index);
char	*find_var_in_env(char *input, char *var_name, char **env);

/* expand2 */
char	*delete_name_and_dollar_sign(char *input, char *var_name);
char	*expand_var(char *input);
int		should_expand(char *input);
char	*weird_cases(char *input);
char	*ft_strjoin_char(char *s1, char c);

/* question_mark */
char	*expand_exit_status(char *input, int dollar_index);
int		handle_var_expansion(char **new_input, char *input, int *i);
int		handle_dollar(char **new_input, char *input, int *i);
int		expand_var_loop(char **new_input, char *input, int i);
void	handle_var_value(char **new_input, char *var_value);

int		handle_var_not_found(char **new_input);
void	append_str(char **dst, const char *src);
void	append_char(char **new_input, char c);
int		handle_exit_status(char **new_input, int *i);
int		is_weird(char *input);
char	*should_not_expand(char *input);
char	*strip_outer_quotes(const char *str);
void	remove_quotes_from_tokens(void);
char	*remove_all_quotes(char *str);
void	remove_empty_args(char **args);

#endif
