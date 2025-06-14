/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:11:07 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 21:38:22 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	not_found1(t_simple_command *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *)cmd->path, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	msh()->exit_status = 127;
}

void	not_found2(const char *fail_path)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *)fail_path, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	msh()->exit_status = 127;
}

static void	handle_is_directory(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		is_a_dir(path);
		free_and_exit(msh());
		exit(126);
	}
}

static void	handle_builtin(t_simple_command *cmd)
{
	if (is_builtin(cmd->array_args[0]))
	{
		execute_builtins(cmd);
		free_and_exit(msh());
		exit(msh()->exit_status);
	}
}

void	child_process(t_simple_command *cmd, char **env)
{
	const char	*exec_path;
	const char	*fail_path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (cmd->path)
		exec_path = cmd->path;
	else
		exec_path = cmd->array_args[0];
	fail_path = cmd->array_args[0];
	decide_fd(cmd);
	close_all_fds_except(STDIN_FILENO, STDOUT_FILENO);
	handle_is_directory(exec_path);
	handle_builtin(cmd);
	cmd_permiss_errors(cmd);
	if (!cmd->path)
		handle_permission_and_not_found(fail_path);
	execve(cmd->path, cmd->array_args, env);
	handle_execve_error(cmd);
}
