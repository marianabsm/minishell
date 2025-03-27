/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:20:57 by marianamest       #+#    #+#             */
/*   Updated: 2025/03/22 21:34:18 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	run_doc(char *delimiter, t_exec *exec, int k)
{
	int	pid;

	if (pipe(exec[k].pipe_fd) < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		safe_close(exec[k].pipe_fd[0]);
		safe_close(exec[k].pipe_fd[1]);
		return (-1);
	}
	if (pid == 0)
		read_into_heredoc(delimiter, exec, k);
	ft_waitpid(pid);
	if (msh()->exit_status == 130)
		return (-1);
	if (msh()->exit_status == 169)
	{
		exec[k].cmd_invalid = true;
		msh()->exit_status = 0;
	}
	return (0);
}

void	read_into_heredoc(char *delimiter, t_exec *exec, int k)
{
	char	*str;

	signal(SIGINT, SIG_DFL);
	safe_close(exec->pipe_fd[0]);
	while (1)
	{
		printf("is here\n");
		str = readline("> ");
		if (!str)
			control_d_handle(exec, k, str);
		if (ft_strcmp(str, delimiter) == 0)
			break ;
		write_to_pipe(str, exec + k);
	}
	safe_close(exec[k].pipe_fd[1]);
	exit(0);
}

void	control_d_handle(t_exec *exec, int k, char *str)
{
	(void)k;
	if (!str)
		return ;
	safe_close(exec->pipe_fd[1]);
	exit(169);
}
