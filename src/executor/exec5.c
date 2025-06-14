/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:10:50 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 21:45:16 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_permiss_errors(t_simple_command *cmd)
{
	check_ls(cmd);
	if (find_path(cmd) == -1)
	{
		if (access(cmd->array_args[0], F_OK) == 0)
		{
			if (access(cmd->array_args[0], X_OK) != 0)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd(cmd->array_args[0], STDERR_FILENO);
				ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
				msh()->exit_status = 126;
				exit(126);
			}
		}
		else
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd->array_args[0], STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			msh()->exit_status = 127;
			exit(127);
		}
	}
}

void	decide_fd(t_simple_command *cmd)
{
	if (cmd->input_fd > 0)
	{
		dup2(cmd->input_fd, STDIN_FILENO);
		if (cmd->input_fd > 2)
			close(cmd->input_fd);
	}
	if (cmd->output_fd > 1)
	{
		dup2(cmd->output_fd, STDOUT_FILENO);
		if (cmd->output_fd > 2)
			close(cmd->output_fd);
	}
}

int	parent_process(t_simple_command *cmd, pid_t pid, int status)
{
	waitpid(pid, &status, 0);
	if (cmd->input_fd > 2)
	{
		close(cmd->input_fd);
		cmd->input_fd = STDIN_FILENO;
	}
	if (cmd->output_fd > 2)
	{
		close(cmd->output_fd);
		cmd->output_fd = STDOUT_FILENO;
	}
	if (WIFEXITED(status))
	{
		msh()->exit_status = WEXITSTATUS(status);
		return (msh()->exit_status);
	}
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		msh()->exit_status = 128 + WTERMSIG(status);
		return (msh()->exit_status);
	}
	signal(SIGINT, sigint_handler);
	return (1);
}
