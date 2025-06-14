/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:10:13 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 14:10:14 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*make_env_entry(const char *name, const char *value)
{
	return (create_env_entry(name, value));
}

static int	fill_env_matrix(char **env_matrix, t_env *env_list)
{
	t_env	*current;
	int		i;

	current = env_list;
	i = 0;
	while (current)
	{
		if (current->valid)
		{
			env_matrix[i] = make_env_entry(current->var_name,
					current->var_value);
			if (!env_matrix[i])
				return (0);
			i++;
		}
		current = current->next;
	}
	env_matrix[i] = NULL;
	return (1);
}

char	**update_env_matrix(t_env *env_list)
{
	char	**env_matrix;

	if (!env_list)
		return (NULL);
	env_matrix = (char **)safe_malloc((get_env_list_size(env_list) + 1)
			* sizeof(char *));
	if (!env_matrix)
		return (NULL);
	if (!fill_env_matrix(env_matrix, env_list))
	{
		free_matrix(env_matrix);
		return (NULL);
	}
	return (env_matrix);
}
