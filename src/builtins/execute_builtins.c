/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 16:58:48 by marianamest       #+#    #+#             */
/*   Updated: 2025/03/22 00:15:27 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_env(t_env *env, int fd)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (current->var_name && current->var_value)
		{
			write(fd, current->var_name, ft_strlen(current->var_name));
			write(fd, "=", 1);
			write(fd, current->var_value, ft_strlen(current->var_value));
			write(fd, "\n", 1);
		}
		current = current->next;
	}
}

int	execute_builtin(t_exec *exec)
{
	if (ft_strcmp(exec->args[0], "cd") == 0) // Tá bom!
		cd(exec->args, exec->out_fd);
	else if (ft_strcmp(exec->args[0], "export") == 0) // Tá bom!
		export_command(exec->args, msh()->env, exec->out_fd);
	else if (ft_strcmp(exec->args[0], "unset") == 0) // Tá bom!
		exec_unset(exec->args);
	else if (ft_strcmp(exec->args[0], "exit") == 0) //Tá Bom!
		exec_exit(exec->args);
	else if (ft_strcmp(exec->args[0], "env") == 0) //Tá bom!
		print_env(msh()->env, exec->out_fd);
	else if (ft_strcmp(exec->args[0], "pwd") == 0) //Tá bom!
		pwd(exec->out_fd);
	else if (ft_strcmp(exec->args[0], "echo") == 0) // a expação de variaveis não está a funcionar de resto tá bom!
		run_echo(exec->args, exec->out_fd);
	else
		return (0);
	return (1);
}


int	is_builtin(char *command) // bota struct maybe
{
	if (ft_strcmp(command, "cd") == 0 || ft_strcmp(command, "export") == 0
		|| ft_strcmp(command, "unset") == 0 || ft_strcmp(command, "exit") == 0
		|| ft_strcmp(command, "env") == 0 || ft_strcmp(command, "pwd") == 0
		|| ft_strcmp(command, "echo") == 0)
	{
		return (1);
	}
	return (0);
}

char	*get_var_value(char *name)
{
	t_env	*env;

	env = msh()->env;
	if (!env)
		return (NULL);
	while (env)
	{
		if (env->next)
		{
			if (ft_strcmp(name, env->next->var_name))
				return (ft_strdup(name));
			env = env->next;
		}
	}
	return (NULL);
}
