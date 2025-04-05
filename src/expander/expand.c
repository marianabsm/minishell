/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:42:49 by marianamest       #+#    #+#             */
/*   Updated: 2025/04/04 18:42:13 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Sempre que tem um $ tenta expandir a menos que esteja entre pelicas especificamente (aspas expande)
// So deixo de ler o nome da var quando encontro um char illegal para nome de var (o nome não pode começar por numero) ✅
// A partir desse momento paro e o que li ate aí é o nome da var ✅
// Procuro nas env vars ✅
// Se estiver la passo o nome para o valor ✅
// Se nao apago o dollar sign e o nome
// Se o primeiro char for invalido char para var name apago o dollar sign ✅
// Se o primeiro char for numero apago dollar sign e número ✅


int find_var_name(char *input)
{
    int i;
    int j;
    
    i = 0;
    if(!input)
        return (0);
    while(input[i])
    {
        if (input[i] == '$')
        {
            i++;
            j = i;
            if(ft_isdigit(input[j])) // se o primeiro char for numero
            {
                /*função para apagar numero e dollar sign*/
            }
            else if(ft_isalnum(input[j]))
            {
                /*função para apagar dollar sign*/
            }
            else
            {
                while(input[j] && (input[j] == '_' || ft_isalnum(input[j]))) //size of var name
                    j++;
            }
            break;
        }
        i++;
    }
    return (j);
}

int find_var_name2(char *input, int size_of_var_name)
{
    int i;
    char *var_name;

    i = 0;
    var_name = (char *)malloc(sizeof(char) * (size_of_var_name + 1));
    if (!var_name)
        return (NULL);
    while (input[i] && (input[i] == '_' || ft_isalnum(input[i])))
        var_name[i++] = input[i++];
    return (var_name);
}

char *find_var_value(char *input, char **env)
{
    int i;
    char *var_name;
    char *var_value;

    i = 0;
    var_name = find_var_name2(input, find_var_name(input));
    if (!var_name)
        return (NULL);
    while (input[i] && (input[i] == '_' || ft_isalnum(input[i])))
        i++;
    if (input[i] == '\0')
        return (NULL);
    var_value = get_env_value(var_name, env);
    free(var_name);
    return (var_value);
}

char *find_var(char *var_name, char **env)
{
    int i;
    
    char *var_value;
    i = 0;
    if (!var_name)
        return (NULL);
    var_value = get_env_value(var_name, env);
    free(var_name);
    return (var_value);
}

get_env_value(char *var_name, char **env)
{
    int i;
    char *var_value;

    i = 0;
    while (env[i])
    {
        if (ft_strncmp(env[i], var_name, ft_strlen(var_name)) == 0)
        {
            var_value = ft_strdup(env[i] + ft_strlen(var_name) + 1);
            return (var_value);
        }
        i++;
    }
    return (NULL);
}