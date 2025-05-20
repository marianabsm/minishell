/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 01:39:20 by msilva-c          #+#    #+#             */
/*   Updated: 2025/05/20 14:10:29 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../includes/minishell.h"

/* expand1.c */
int		find_and_size_var_name(char *input);
char	*find_var_name2(char *input, int size_of_var_name);
char	*delete_number_and_dollar_sign(char *input, int dollar_index);
char	*delete_dollar_sign(char *input, int dollar_index);
char	*find_var_in_env(char *input, char *var_name, char **env);

/* expand2.c */
char	*delete_name_and_dollar_sign(char *input, char *var_name);
char	*expand_var(char *input);
int		should_expand(char *input);
char	*weird_cases(char *input);
char	*ft_strjoin_char(char *s1, char c);

#endif
