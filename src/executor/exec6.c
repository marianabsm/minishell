/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:10:54 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 21:39:05 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	handle_empty_command(t_simple_command *cmd)
{
	if (!cmd || !cmd->array_args || !cmd->array_args[0]
		|| cmd->array_args[0][0] == '\0')
	{
		msh()->exit_status = 0;
		return (1);
	}
	return (0);
}

static int	handle_single_builtin(t_simple_command *cmd)
{
	if (is_builtin(cmd->array_args[0]) && msh()->exec->nbr_cmds == 1)
	{
		execute_builtins(cmd);
		return (1);
	}
	return (0);
}

int	execute_command(t_simple_command *cmd, char **env)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (handle_empty_command(cmd))
		return (0);
	if (handle_single_builtin(cmd))
		return (msh()->exit_status);
	pid = fork();
	if (pid < 0)
		return (fork_error());
	if (pid == 0)
	{
		child_process(cmd, env);
		free_and_exit(msh());
		exit(msh()->exit_status);
	}
	else
		return (parent_process(cmd, pid, status));
	return (msh()->exit_status);
}

void	handle_permission_and_not_found(const char *fail_path)
{
	struct stat	st;

	if (stat(fail_path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		is_a_dir(fail_path);
		free_and_exit(msh());
		exit(126);
	}
	if (access(fail_path, F_OK) == 0)
	{
		perm_den(fail_path);
		free_and_exit(msh());
		exit(126);
	}
	else
	{
		not_found2(fail_path);
		free_and_exit(msh());
		exit(127);
	}
}

void	handle_execve_error(t_simple_command *cmd)
{
	if (access(cmd->path, F_OK) == 0)
	{
		perm_den(cmd->path);
		free_and_exit(msh());
		exit(126);
	}
	else
	{
		not_found1(cmd);
		free_and_exit(msh());
		exit(127);
	}
}
