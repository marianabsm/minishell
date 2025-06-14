/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:10:56 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 14:10:57 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_access(t_simple_command *cmd, char **paths, int i)
{
	char	*semi_path;
	char	*full_path;

	semi_path = ft_strjoin(paths[i], "/");
	full_path = ft_strjoin(semi_path, cmd->array_args[0]);
	free(semi_path);
	if (access(full_path, X_OK) == 0)
	{
		cmd->path = full_path;
		free_matrix(paths);
		return (0);
	}
	free(full_path);
	return (1);
}

static int	handle_slash_case(t_simple_command *cmd)
{
	if (access(cmd->array_args[0], F_OK) == 0)
	{
		if (access(cmd->array_args[0], X_OK) == 0)
			return (0);
		else
			return (-1);
	}
	else
		return (-1);
}

static int	handle_no_slash_case(t_simple_command *cmd, char *path_env)
{
	char	**paths;
	int		i;

	if (access(cmd->array_args[0], X_OK) == 0)
	{
		cmd->path = cmd->array_args[0];
		return (0);
	}
	paths = ft_split(path_env, ':');
	i = 0;
	while (paths[i])
	{
		if (check_access(cmd, paths, i) == 0)
			return (0);
		i++;
	}
	free_matrix(paths);
	return (-1);
}

int	find_path(t_simple_command *cmd)
{
	char	*path_env;

	path_env = getenv("PATH");
	if (!path_env)
		return (-1);
	if (ft_strchr(cmd->array_args[0], '/'))
	{
		cmd->path = cmd->array_args[0];
		return (handle_slash_case(cmd));
	}
	return (handle_no_slash_case(cmd, path_env));
}
