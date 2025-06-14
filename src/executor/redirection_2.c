/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:36:18 by msilva-c          #+#    #+#             */
/*   Updated: 2025/06/05 15:19:06 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_l(t_exec *ex, char *value)
{
	safe_close(ex->in_pipe_fd[0]);
	ex->in_pipe_fd[0] = open(value, O_RDONLY);
	if (ex->in_pipe_fd[0] < 0)
	{
		perror("Error opening file for input redirection");
		return (0);
	}
	if (dup2(ex->in_pipe_fd[0], STDIN_FILENO) < 0)
	{
		perror("dup2 failed");
		return (0);
	}
	return (1);
}

int	exec_red2(t_exec *ex, char *key, char *value)
{
	int	ret;

	ret = 0;
	if (!ft_strncmp(key, ">", 1))
		ret = exec_r(ex, value);
	else if (!ft_strncmp(key, "<", 1))
		ret = exec_l(ex, value);
	else if (!strncmp(key, ">>", 2))
		ret = exec_rr(ex, value);
	return (ret);
}

void	start_execution(t_exec *ex, int index)
{
	if (index > 0)
		safe_close(msh()->exec[index - 1].in_pipe_fd[0]);
	close_pipe(ex->in_pipe_fd);
}
