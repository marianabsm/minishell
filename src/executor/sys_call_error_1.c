/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_call_error_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:42:43 by msilva-c          #+#    #+#             */
/*   Updated: 2025/03/22 13:34:50 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *get_path(t_env *env)
{
	while (env)
	{
		if (!ft_strncmp(env->var_name, "PATH", 5))
			return (env->var_value);
		env = env->next;
	}
	return (NULL);
}

char *path_search(char *str, t_env *env)
{
	int i = 0;
	char *tmp;
	char *path = get_path(env);

	tmp = NULL;
	if (!path)
		return (ft_strdup(str));
	char **ret = ft_split(path, ':');
	while(ret && ret[i])
	{
		if (ft_check_access(ft_strjoin(ret[i], "/"), str, &tmp))
			break;
		i++;
	}
	free_matrix(ret);
	if (!tmp)
		return (ft_strdup(str));
	return (tmp);
}

int	pipe_error(void)
{
	perror("pipe");
	msh()->exit_status = 1;
	return (-1);
}

void	close_fds(int *fds)
{
	safe_close(fds[0]);
	safe_close(fds[1]);
}

int	fork_error(void)
{
	perror("fork");
	msh()->exit_status = 1;
	return (-1);
}
