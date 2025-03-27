/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_executer_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 10:03:52 by msilva-c          #+#    #+#             */
/*   Updated: 2025/03/22 16:32:54 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void execute_loop(t_exec *ex, int in, int out)
{
	int i = 0;
	while (i < msh()->exec->nbr_cmds)
	{
		out = STDOUT_FILENO;
		if (i + 1 < msh()->exec->nbr_cmds)
		{
			pipe(ex[i].pipe_fd);
			out = ex[i].pipe_fd[1];
		}
		if (ex[i].out_fd)
		{
			safe_close(out);
			out = ex[i].out_fd;
		}
		if (ex[i].in_fd)
		{
			safe_close(in);
			in = ex[i].in_fd;
		}
		exec_single_cmd(&ex[i], in, out);
		in = ex[i].pipe_fd[0];
		i++;
	}
}


void start_executing(void)
{
	int i = -1;
	int pid;

	t_exec *ex;
	ex = msh()->exec;
	if (!check_redirs(ex))
		return ;
	ex = msh()->exec;
	if (msh()->exec->nbr_cmds == 1)
		exec_single_cmd(ex, 0, 1);
	else
	{
		pid = fork();
		if (pid == 0)
			execute_loop(ex, STDIN_FILENO, STDOUT_FILENO);
		else
			ft_waitpid(pid);
	}
	i = -1;
	while (++i < msh()->exec->nbr_cmds)
		ft_waitpid(-1);
	main_signals();
}
