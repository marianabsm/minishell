/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:20:31 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/08 22:17:42 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*create_env_entry(const char *key, const char *value)
{
	int		key_len;
	int		value_len;
	char	*entry;

	if (!key)
		return (NULL);
	if (!value)
		return (ft_strdup(key));
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
	ft_strncpy(key, env_var, key_len);
	key[key_len] = '\0';
	value = equal_sign + 1;
	env[i] = create_env_entry(key, value);
	free(key);
	if (!env[i])
		return (0);
	return (1);
}

void	bi_env(t_simple_command *cmd)
{
	char	**tmp;
	int		i;

	if (cmd->n_of_arg > 1)
	{
		printf("Too many arguments\n");
		return ;
	}
	tmp = msh()->env;
	i = -1;
	while (tmp[++i])
		printf("%s\n", tmp[i]);
}

char	**add_to_env(char **env, char *new_var)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (env);
	i = 0;
	while (env && env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = ft_strdup(new_var);
	new_env[i + 1] = NULL;
	if (env)
		free_matrix(env);
	return (new_env);
}
