/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrito- <mabrito-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 01:39:20 by msilva-c          #+#    #+#             */
/*   Updated: 2025/04/05 19:25:51 by mabrito-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../includes/minishell.h"

/* expander_1.c */
int     is_edge_expand(char *var_name);
char    *edge_expand(char *var_name, t_msh *msh);
char    *regular_expand(t_env *env, char *var_name);
char    *update_content(t_token *token, char *old, char *expanded);
// void    expander(t_token *tokens);

/* expander_2.c */
int		var_name_len(char *str, int i);
char	*grep_var_name(t_token *token);
int		expanded_strlen(char *old, char *var_value);

/* expander_3.c */
int		needs_expansion(t_token *token);
// void	expand_var(t_token *token, t_msh *msh);
void	ignore_dollar(char *str);
void	put_dollar_back(char *str);

/* expand1.c */
int		find_and_size_var_name(char *input);
char    *find_var_name2(char *input, int size_of_var_name);
char	*delete_number_and_dollar_sign(char *input, int dollar_index);
char	*delete_dollar_sign(char *input, int dollar_index);
char	*find_var_in_env(char *input, char *var_name, char **env);

/* expand2.c */
char	*delete_name_and_dollar_sign(char *input, char *var_name);
char	*expand_var(char *input);
int     should_expand(char *input);

#endif
