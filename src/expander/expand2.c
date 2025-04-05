/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrito- <mabrito-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:42:49 by marianamest       #+#    #+#             */
/*   Updated: 2025/04/05 17:29:51 by mabrito-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// $USER -> expande (mabrito-)
// "$USER" -> expande (mabrito-)

// '$USER' -> $USER

// $'USER' -> USER
// $"USER" -> USER

int should_expand(char *input) // receives a pointer to the part of the input string where either ' , " or $ was found
{
    if (!input || ft_strlen(input) < 2)
        return (0);
    if (input[0] == '\'' && input[ft_strlen(input) - 1] == '\'')
        return (0);
    if (input[0] == '"' && input[ft_strlen(input) - 1] == '"')
        return (1);
    if (input[0] == '$' && input[1] == '\'')
        return (0);
    if (input[0] == '$' && input[1] == '"')
        return (1);
    if (input[0] == '$')
        return (1);
    return (0);
}


char *delete_name_and_dollar_sign (char *input, char *var_name)
{
    char *new_input;
    int i;
    int j;
    
    j = 0;
    i = 0;
    new_input = (char *)malloc(sizeof(char) * (ft_strlen(input) - ft_strlen(var_name) - 1)); // -1 for the dollar sign
    if (!new_input)
        return (NULL);
    while(input[i] && input[i] != '$')
        new_input[j++] = input[i++];
    i += ft_strlen(var_name) + 1; // +1 for the dollar sign
    while(input[i] && input[j])
        new_input[j++] = input[i++];
    return(new_input);
}

char *expand_var(char *input, t_token *token)
{
    char *var_name;
    char *var_value;
    int i;

    i = 0;
    while (token->content[i])
    {
        if (token->content[i] == '$'|| token->content[i] == '\'' || token->content[i] == '"')
        {
            if(should_expand(&token->content[i]))
            {
                var_name = find_var_name2(input, find_and_size_var_name(input));
                var_value = find_var_in_env(input, var_name, msh()->env);
                if (var_value)
                {
                    token->content = ft_strjoin(token->content, var_value);
                    free(var_value);
                }
            }
        }
        i++;
    }
    return (token->content);
}

