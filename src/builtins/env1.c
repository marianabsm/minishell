/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:20:31 by marianamest       #+#    #+#             */
/*   Updated: 2025/03/20 21:38:47 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*create_env_entry(const char *key, const char *value)
{
	int		key_len;
	int		value_len;
	char	*entry;

	key_len = ft_strlen(key);
	value_len = ft_strlen(value);
	entry = (char *)safe_malloc(key_len + value_len + 2);
	if (!entry)
		return (NULL);
	my_strcpy(entry, key);
	my_strcat(entry, "=");
	my_strcat(entry, value);
	return (entry);
}

char	**allocate_env(char **envp)
{
	int		i;
	char	**env;

	i = 0;
	while (envp[i])
		i++;
	env = (char **)safe_malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	return (env);
}

int	process_env_variable(char *env_var, char **env, int i)
{
	char	*equal_sign;
	int		key_len;
	char	*key;
	char	*value;

	equal_sign = env_var;
	while (*equal_sign && *equal_sign != '=')
		equal_sign++;
	key_len = equal_sign - env_var;
	key = (char *)safe_malloc(key_len + 1);
	if (!key)
		return (0);
	my_strcpy(key, env_var);
	value = equal_sign + 1;
	env[i] = create_env_entry(key, value);
	free(key);
	if (!env[i])
		return (0);
	return (1);
}

char	**init_env_array(char **envp)
{
	int		i;
	char	**env;

	i = 0;
	env = NULL;
	if (!check_env(envp))
		free_matrix(envp);
	else
	{
		env = allocate_env(envp);
		if (!env)
			return (NULL);
		while (envp[i])
		{
			if (!process_env_variable(envp[i], env, i))
			{
				while (i > 0)
					free(env[--i]);
				free(env);
				return (NULL);
			}
			i++;
		}
		env[i] = NULL;
	}
	return (env);
}
