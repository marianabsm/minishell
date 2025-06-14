/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:31:53 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/09 21:08:21 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	select_builtin(t_simple_command *cmd)
{
	if (ft_strcmp(cmd->array_args[0], "cd") == 0)
		cd(cmd->array_args);
	else if (ft_strcmp(cmd->array_args[0], "echo") == 0)
	{
		run_echo(cmd->array_args, cmd->output_fd);
		msh()->exit_status = 0;
	}
	else if (ft_strcmp(cmd->array_args[0], "exit") == 0)
		exec_exit(cmd->array_args);
	else if (ft_strcmp(cmd->array_args[0], "export") == 0)
		export_command(cmd->array_args, msh()->env_list, cmd->output_fd);
	else if (ft_strcmp(cmd->array_args[0], "unset") == 0)
		exec_unset(cmd->array_args);
	else if (ft_strcmp(cmd->array_args[0], "env") == 0)
		bi_env(cmd);
	else if (ft_strcmp(cmd->array_args[0], "pwd") == 0)
		pwd(cmd->output_fd);
}

int	is_builtin(char *command)
{
	if (ft_strcmp(command, "cd") == 0 || ft_strcmp(command, "echo") == 0
		|| ft_strcmp(command, "exit") == 0 || ft_strcmp(command, "export") == 0
		|| ft_strcmp(command, "unset") == 0 || ft_strcmp(command, "env") == 0)
		return (1);
	return (0);
}

void	execute_builtins(t_simple_command *cmd)
{
	if (cmd->input_fd < 0 || cmd->output_fd < 0)
		return ;
	msh()->exit_status = 0;
	if (cmd->input_fd > 0)
		dup2(cmd->input_fd, STDIN_FILENO);
	if (cmd->output_fd > 1)
		dup2(cmd->output_fd, STDOUT_FILENO);
	select_builtin(cmd);
}
