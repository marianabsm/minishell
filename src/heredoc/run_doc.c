/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:20:57 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/08 21:09:50 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	handle_fork_error(int pipe_doc[2])
{
	safe_close(pipe_doc[0]);
	safe_close(pipe_doc[1]);
	return (-1);
}

static int	validate_heredoc_args(t_command_table *table, t_redirs_list *redir,
		int pipe_doc[2])
{
	if (!redir || !redir->delimiter || *redir->delimiter == '\0')
	{
		ft_putstr_fd("Error: Invalid heredoc delimiter\n", STDERR_FILENO);
		handle_fork_error(pipe_doc);
		return (0);
	}
	if (!table || !table->simplecommand)
	{
		handle_fork_error(pipe_doc);
		return (0);
	}
	return (1);
}

static int	handle_child_and_wait(t_redirs_list *redir, int pipe_doc[2])
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (handle_fork_error(pipe_doc));
	if (pid == 0)
		read_into_heredoc(redir, pipe_doc);
	ft_waitpid(pid);
	return (pid);
}

static int	handle_heredoc_interrupt(int pipe_doc[2], t_command_table *table)
{
	if (msh()->exit_status == 130)
	{
		handle_fork_error(pipe_doc);
		table->simplecommand->input_fd = STDIN_FILENO;
		return (1);
	}
	return (0);
}

int	run_doc(t_command_table *table, t_redirs_list *redir)
{
	int	pipe_doc[2];
	int	pid;

	if (pipe(pipe_doc) < 0)
		return (-1);
	if (!validate_heredoc_args(table, redir, pipe_doc))
		return (-1);
	pid = handle_child_and_wait(redir, pipe_doc);
	if (pid < 0)
		return (-1);
	if (handle_heredoc_interrupt(pipe_doc, table))
		return (-1);
	table->simplecommand->input_fd = pipe_doc[0];
	safe_close(pipe_doc[1]);
	return (0);
}
