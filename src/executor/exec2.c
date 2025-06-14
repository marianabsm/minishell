/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:11:12 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 19:31:18 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_all_fds_except(int in_fd, int out_fd)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
	{
		if (fd != in_fd && fd != out_fd)
			close(fd);
		fd++;
	}
}

void	close_pipes(t_exec *exec)
{
	if (exec->in_pipe_fd[0] != -1)
		close(exec->in_pipe_fd[0]);
	if (exec->in_pipe_fd[1] != -1)
		close(exec->in_pipe_fd[1]);
	if (exec->out_pipe_fd[0] != -1)
		close(exec->out_pipe_fd[0]);
	if (exec->out_pipe_fd[1] != -1)
		close(exec->out_pipe_fd[1]);
}

void	close_in_exec(t_exec *exec)
{
	exec->in_pipe_fd[1] = -1;
	exec->in_pipe_fd[0] = exec->in_pipe_fd[1];
	exec->out_pipe_fd[1] = -1;
	exec->out_pipe_fd[0] = exec->out_pipe_fd[1];
}

char	**skip_empty_args(char **args)
{
	int		i;
	int		j;
	char	**new_args;

	i = 0;
	j = 0;
	new_args = malloc(sizeof(char *) * (size_args(args) + 1));
	if (!new_args)
		return (args);
	i = 0;
	j = 0;
	while (args && args[i])
	{
		if (args[i][0] != '\0')
			new_args[j++] = ft_strdup(args[i]);
		i++;
	}
	new_args[j] = NULL;
	if (args)
		free_matrix(args);
	return (new_args);
}
