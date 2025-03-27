/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrito- <mabrito-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:20:57 by marianamest       #+#    #+#             */
/*   Updated: 2025/03/27 16:40:27 by mabrito-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	run_doc(char *delimiter, t_exec *exec, int k)
{
	int	pid;

	if (pipe(exec[k].pipe_fd) < 0)
		return(-1);
	// if(!delimiter || *delimiter == '\0') // problem
	// {
	// 	ft_put_str_fd("Error: Invalid heredoc delimiter\n", STDERR_FILENO);
	// 	return (-1);
	// }
	if (!delimiter || *delimiter == '\0')
{
    ft_put_str_fd("Error: Invalid heredoc delimiter\n", STDERR_FILENO);
    fprintf(stderr, "Debug: delimiter is '%s'\n", delimiter ? delimiter : "(null)");
    return (-1);
}
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
    signal(SIGQUIT, SIG_IGN);
    safe_close(exec->pipe_fd[0]);
    while (1)
    {
        str = readline("> ");
        if (!str)
            control_d_handle(exec, k, str);
        if (ft_strcmp(str, delimiter) == 0)
		{
			free(str);
			break;
		}
        write_to_pipe(str, exec + k);
        free(str);
    }
    safe_close(exec[k].pipe_fd[1]);
    exit(0);
}

void	control_d_handle(t_exec *exec, int k, char *str)
{
    (void)k;
    if (!str)
    {
        safe_close(exec->pipe_fd[1]);
        write(STDOUT_FILENO, "\n", 1);
        exit(130);
    }
}
