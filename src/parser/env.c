/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:45:59 by marianamest       #+#    #+#             */
/*   Updated: 2025/04/04 16:05:08 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


char **duplicate_envp(char **envp)
{
    char **env;
    int i;
    int env_count;
    
    env_count = 0;
    while (envp[env_count])
        env_count++;
    env = malloc(sizeof(char *) * (env_count + 1));
    if (!env)
    {
        ft_putstr_fd("Error: Malloc failed", STDERR_FILENO);
        return (NULL);
    }
    i = 0;
    while (envp[i])
    {
        env[i] = ft_strdup(envp[i]);
        if (!env[i])
        {
            while (i > 0)
            {
                free(env[i]);
                i--;
            }
            free(env);
            return (NULL);
        }
        i++;
    }
    env[i] = NULL;
    return (env);
}

void free_env(char **env)
{
    int i = 0;

    if (!env)
        return;

    while (env[i])
    {
        free(env[i]);
        i++;
    }
    free(env);
}