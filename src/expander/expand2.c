/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrito- <mabrito-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:42:49 by marianamest       #+#    #+#             */
/*   Updated: 2025/04/05 21:36:15 by mabrito-         ###   ########.fr       */
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

char *ft_strjoin_char(char *s1, char c)
{
    char *result;
    int len;

    if (!s1)
        return (NULL);
    len = ft_strlen(s1);
    result = malloc(sizeof(char) * (len + 2));
    if (!result)
        return (NULL);
    ft_strcpy(result, s1);
    result[len] = c;
    result[len + 1] = '\0';
    return (result);
}

char *expand_var(char *input)
{
    char *var_name;
    char *var_value;
    char *new_input;
    char *temp;
    int i;
    int var_size;

    new_input = ft_strdup("");
    i = 0;
    while (input[i])
    {
        if (input[i] == '$' && should_expand(&input[i]))
        {
            var_size = find_and_size_var_name(&input[i]);
            var_name = find_var_name2(&input[i], var_size);
            var_value = find_var_in_env(input, var_name, msh()->env);
            if (var_value)
            {
                free(new_input);
                new_input = temp;
                free(var_value);
            }
            free(var_name);
            i += var_size + 1; // Skip the variable name and '$'
        }
        else
        {
            temp = ft_strjoin_char(new_input, input[i]); // Append the current character
            free(new_input);
            new_input = temp;
            i++;
        }
    }
    return (new_input);
}
