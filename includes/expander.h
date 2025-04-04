/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 01:39:20 by msilva-c          #+#    #+#             */
/*   Updated: 2025/04/04 16:17:03 by marianamest      ###   ########.fr       */
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

#endif
