/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:10:45 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 14:10:46 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pre_exec_parse(t_command_table *current_cmd)
{
	if (current_cmd->simplecommand && current_cmd->simplecommand->array_args)
		current_cmd->simplecommand->array_args = \
		skip_empty_args(current_cmd->simplecommand->array_args);
	if (!current_cmd || !current_cmd->simplecommand
		|| !current_cmd->simplecommand->array_args
		|| !current_cmd->simplecommand->array_args[0])
		return (0);
	return (1);
}

int	pipe_problem(t_exec *exec, t_command_table *current_cmd)
{
	if (current_cmd->next && pipe(exec->out_pipe_fd) < 0)
	{
		perror("minishell: pipe");
		return (0);
	}
	return (1);
}

int	built_in_start(t_command_table *current_cmd)
{
	if (current_cmd && current_cmd->simplecommand
		&& current_cmd->simplecommand->array_args
		&& current_cmd->simplecommand->array_args[0]
		&& is_builtin(current_cmd->simplecommand->array_args[0])
		&& !current_cmd->next)
	{
		execute_builtins(current_cmd->simplecommand);
		return (1);
	}
	return (0);
}

int	cmd_loop(t_exec *exec, t_command_table *current_cmd, int last_status)
{
	while (current_cmd)
	{
		if (!pre_exec_parse(current_cmd))
			break ;
		if (!pipe_problem(exec, current_cmd))
			return (-1);
		if (built_in_start(current_cmd))
		{
			last_status = msh()->exit_status;
			current_cmd = current_cmd->next;
			continue ;
		}
		exec->pid[exec->index] = fork();
		if (exec->pid[exec->index] < 0)
			fork_error();
		if (exec->pid[exec->index] == 0)
			child_p(exec, current_cmd);
		else
		{
			daddy_p(exec, current_cmd);
			exec->index++;
			current_cmd = current_cmd->next;
		}
	}
	return (last_status);
}
