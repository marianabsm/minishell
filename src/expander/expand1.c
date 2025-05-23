/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:42:49 by marianamest       #+#    #+#             */
/*   Updated: 2025/05/20 14:09:03 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int find_and_size_var_name(char *input) // finds var name in the input string
{
    int i;
    int j;

    i = 0;
    if (!input)
        return (0);
    while (input[i])
    {
        if (input[i] == '$')
        {
            j = i;
            i++;
            if (input[i] == '"')
                i++;
            if (ft_isdigit(input[i]))
                return (0);
            else if (!ft_isalnum(input[i]) && input[i] != '_')
                return (0);
            while (input[i] && (input[i] == '_' || ft_isalnum(input[i])))
                i++;
            if (input[i] == '"')
                i++;
            return (i - j - 1);
        }
        i++;
    }
    return (0);
}

char *find_var_name2(char *input, int size_of_var_name) // finds var name in the input string
{
    int i;
    int j;
    char *var_name;

    if (size_of_var_name <= 0)
        return (NULL);

    var_name = malloc(sizeof(char) * (size_of_var_name + 1));
    if (!var_name)
        return (NULL);
    i = 0;
    while (input[i] != '$')
        i++;
    i++;
    if (input[i] == '"')
        i++;
    j = 0;
    while (input[i] && (input[i] == '_' || ft_isalnum(input[i])))
    {
        var_name[j++] = input[i++];
    }
    var_name[j] = '\0';
    return (var_name);
}


char *find_var_in_env(char *input, char *var_name, char **env) // looks through the env to find the var value
{
    int i;
    char *var_value;

    i = 0;
    var_value = NULL;
    printf("var_name: %s\n", var_name);
    while (env[i])
    {
        if (ft_strncmp(env[i], var_name, ft_strlen(var_name)) == 0 &&
            env[i][ft_strlen(var_name)] == '=')
        {
            var_value = ft_strdup(env[i] + ft_strlen(var_name) + 1);
            return (var_value);
        }
        i++;
    }
    delete_name_and_dollar_sign(input, var_name);
    return (NULL);
}

char *delete_number_and_dollar_sign(char *input, int dollar_index) // deletes the number and dollar sign from the input
{
    char *new_input;
    int j;

    new_input = (char *)malloc(sizeof(char) * (ft_strlen(input) - 2));
    if (!new_input)
        return (NULL);
    j = 0;
    while (input[j])
    {
        if (j == dollar_index || j == dollar_index + 1)
            j++;
        new_input[j] = input[j];
        j++;
    }
    new_input[j] = '\0';
    free(input);
    return (new_input);
}

char *delete_dollar_sign(char *input, int dollar_index) // deletes the dollar sign from the input
{
    char *new_input;
    int j;

    new_input = (char *)malloc(sizeof(char) * (ft_strlen(input) - 1));
    if (!new_input)
        return (NULL);
    j = 0;
    while (input[j])
    {
        if (j == dollar_index)
            j++;
        new_input[j] = input[j];
        j++;
    }
    new_input[j] = '\0';
    free(input);
    return (new_input);
}