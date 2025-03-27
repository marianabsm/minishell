/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:07:55 by marianamest       #+#    #+#             */
/*   Updated: 2025/03/22 21:23:34 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_valid_var_char(char c, int is_first_char)
{
	if (is_first_char)
		return (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
	else
		return (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
			|| (c >= '0' && c <= '9'));
}

int	parse_export(char *str)
{
	int	i;

	i = 0;
	if (!is_valid_var_char(str[i], 1))
		return (0);
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!is_valid_var_char(str[i], 0))
			return (0);
		i++;
	}
	return (1);
}

void	format_export_var(const char *var, int fd)
{
	const char	*equals = ft_strchr(var, '=');
	int			name_len;

	(void)fd;
	if (!equals)
		printf("declare -x %s\n", var);
	else
	{
		name_len = equals - var;
		printf("declare -x %.*s=\"%s\"\n", name_len, var, equals + 1);
	}
}

int	find_var_index(char **env, const char *var, int name_len)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, name_len) == 0 && (env[i][name_len] == '='
				|| env[i][name_len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

void	add_new_var(char **env, const char *var)
{
	int		env_size;
	char	**new_env;
	int		i;

	env_size = 0;
	while (env[env_size])
		env_size++;
	new_env = safe_malloc((env_size + 2) * sizeof(char *));
	if (!new_env)
	{
		perror("malloc failed");
		exit(1);
	}
	i = 0;
	while (i < env_size)
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[env_size] = ft_strdup(var);
	new_env[env_size + 1] = NULL;
	free(*env);
	env = new_env;
}
