/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:12:36 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 21:38:12 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	built_or_cmd(t_command_table *current_cmd)
{
	char	*cmd;

	cmd = current_cmd->simplecommand->array_args[0];
	if (cmd && ft_strcmp(cmd, "$?") == 0)
	{
		ft_putstr_fd("minishell: $?: command not found\n", STDERR_FILENO);
		msh()->exit_status = 127;
		free_and_exit(msh());
		exit(127);
	}
	if (is_builtin(cmd))
	{
		execute_builtins(current_cmd->simplecommand);
		free_and_exit(msh());
		exit(msh()->exit_status);
	}
	else
	{
		msh()->exit_status = execute_command(current_cmd->simplecommand,
			msh()->env);
		free_and_exit(msh());
		exit(msh()->exit_status);
	}
}

static void	wait_all(t_exec *exec, int status, int last_status, int i)
{
	if (waitpid(exec->pid[i], &status, 0) == -1)
	{
		perror("minishell: waitpid");
		last_status = 1;
	}
	else if (WIFEXITED(status))
	{
		last_status = WEXITSTATUS(status);
		msh()->exit_status = last_status;
	}
	else if (WIFSIGNALED(status))
	{
		last_status = 128 + WTERMSIG(status);
		msh()->exit_status = last_status;
		if (WTERMSIG(status) == SIGINT)
			ft_putstr_fd("\n", STDERR_FILENO);
		else if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	}
}

void	daddy_p(t_exec *exec, t_command_table *current_cmd)
{
	if (exec->in_pipe_fd[0] != -1)
		close(exec->in_pipe_fd[0]);
	if (exec->in_pipe_fd[1] != -1)
		close(exec->in_pipe_fd[1]);
	exec->in_pipe_fd[0] = exec->out_pipe_fd[0];
	exec->in_pipe_fd[1] = exec->out_pipe_fd[1];
	exec->out_pipe_fd[1] = -1;
	exec->out_pipe_fd[0] = exec->out_pipe_fd[1];
	if (current_cmd->simplecommand->input_fd > 2)
	{
		close(current_cmd->simplecommand->input_fd);
		current_cmd->simplecommand->input_fd = STDIN_FILENO;
	}
	if (current_cmd->simplecommand->output_fd > 2)
	{
		close(current_cmd->simplecommand->output_fd);
		current_cmd->simplecommand->output_fd = STDOUT_FILENO;
	}
}

void	child_p(t_exec *exec, t_command_table *current_cmd)
{
	if (current_cmd->simplecommand->input_fd > 0)
	{
		dup2(current_cmd->simplecommand->input_fd, STDIN_FILENO);
		if (current_cmd->simplecommand->input_fd > 2)
			close(current_cmd->simplecommand->input_fd);
	}
	else if (exec->in_pipe_fd[0] != -1)
		dup2(exec->in_pipe_fd[0], STDIN_FILENO);
	if (current_cmd->simplecommand->output_fd > 1)
	{
		dup2(current_cmd->simplecommand->output_fd, STDOUT_FILENO);
		if (current_cmd->simplecommand->output_fd > 2)
			close(current_cmd->simplecommand->output_fd);
	}
	else if (current_cmd->next && exec->out_pipe_fd[1] != -1)
		dup2(exec->out_pipe_fd[1], STDOUT_FILENO);
	close_pipes(exec);
	built_or_cmd(current_cmd);
}

int	start_executing(t_exec *exec, t_command_table *cmd_table)
{
	t_command_table	*current_cmd;
	int				status;
	int				last_status;
	int				i;

	status = 0;
	last_status = 0;
	i = -1;
	current_cmd = cmd_table;
	if (!cmd_table)
		return (-1);
	close_in_exec(exec);
	last_status = cmd_loop(exec, current_cmd, last_status);
	if (last_status == -1)
		return (-1);
	while (++i < exec->index)
		wait_all(exec, status, last_status, i);
	close_pipes(exec);
	exec->index = 0;
	return (last_status);
}
