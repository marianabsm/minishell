/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:10:09 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 14:10:10 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*matrix_env_join(t_env *temp)
{
	char	*tmp;
	char	*env_str;

	env_str = ft_strjoin(temp->var_name, "=");
	tmp = env_str;
	env_str = ft_strjoin(env_str, temp->var_value);
	free(tmp);
	return (env_str);
}

static int	env_sizer(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

char	**get_matrix_env(t_env *env)
{
	t_env	*temp;
	char	**matrix_env;
	int		i;
	char	*env_str;

	temp = env;
	matrix_env = (char **)safe_malloc((env_sizer(env) + 1) * sizeof(char *));
	temp = env;
	i = 0;
	while (temp && matrix_env)
	{
		if (temp->var_value)
			env_str = matrix_env_join(temp);
		else
			env_str = ft_strdup(temp->var_name);
		matrix_env[i] = env_str;
		i++;
		temp = temp->next;
	}
	matrix_env[i] = NULL;
	return (matrix_env);
}

void	print_sorted_env(t_env *env, int fd)
{
	char	**temp_env;
	int		env_size;
	int		i;
	int		j;

	temp_env = get_matrix_env(env);
	env_size = strlen_args(temp_env);
	i = 0;
	while (i < env_size - 1)
	{
		j = i + 1;
		while (j < env_size)
		{
			if (ft_strcmp(temp_env[i], temp_env[j]) > 0)
				ft_swap(&temp_env[i], &temp_env[j]);
			j++;
		}
		i++;
	}
	i = -1;
	while (temp_env[++i])
	{
		format_export_var(temp_env[i], fd);
	}
	free_matrix(temp_env);
}

int	get_env_list_size(t_env *env_list)
{
	int		size;
	t_env	*current;

	size = 0;
	current = env_list;
	while (current)
	{
		if (current->valid)
			size++;
		current = current->next;
	}
	return (size);
}
