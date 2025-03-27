/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_executer_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:59:02 by msilva-c          #+#    #+#             */
/*   Updated: 2025/03/22 12:23:43 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//rever se só tou a chamar isto numa child


static void	excve_perror(char *command)
{
	t_env	*current;
	bool	has_path;

	has_path = false;
	current = msh()->env;
	while (current)
	{
		if (!ft_strncmp(current->var_name, "PATH", 5))
			has_path = true;
		current = current->next;
	}
	write(2, "minishell: ", 11);
	write(2, command, ft_strlen(command));
	if (has_path)
		write(2, ": command not found\n", 20);
	else
		write(2, ": No such file or directory\n", 28);
}

void	close_args_fds(t_exec *ex)
{
	int index;

	index = ex->index;
	if (!ex)
		exit(1) ;
	if (ex->is_heredoc)
		safe_close(ex->pipe_doc[0]);
	if (ex->index > 0)
		safe_close(msh()->exec[index-1].pipe_fd[0]);
	if (ex->index < ex->nbr_cmds - 1)
		close_pipe(ex->pipe_fd);
	exit(1);
}

void new_child(t_exec *ex)
{
	char	**envp;
	char	*path;

	envp = get_matrix_env(msh()->env);
	if (!ex || ex->cmd_invalid)
		close_args_fds(ex);
	if (!ex->args)
		exit(0);
	if (is_builtin(ex->args[0]))
		execute_builtin(ex);
	else
	{
		if (!ft_strchr(ex->args[0], '/'))
			path = path_search(ex->args[0], msh()->env);
		else
			path = ex->args[0];
		execve(path, ex->args, envp);
		excve_perror(ex->args[0]);
	}
	free_matrix(envp);
	exit(127);
}

void exec_single_cmd(t_exec *ex, int in, int out)
{
	if (ex->cmd_invalid)
		return ;
	if (is_builtin(ex->args[0]))
		execute_builtin(ex);
	else
	{
		signals_ignore();
		ex->pid = fork();
		if (ex->pid == -1)
		{
			perror("fork");
			msh()->exit_status = 1;
			return ;
		}
		if (ex->pid == 0)
		{
			signals_default();
			dup2(in, STDIN_FILENO);
			dup2(out, STDOUT_FILENO);
			safe_close(in);
			safe_close(out);
			new_child(ex);
		}
	}
	safe_close(in);
	safe_close(out);
}
