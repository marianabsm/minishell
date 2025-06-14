/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:13:31 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 14:13:32 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	handle_input_redir(t_command_table *cmd, t_redirs_list *redir)
{
	if (cmd->simplecommand->input_fd > 2)
	{
		close(cmd->simplecommand->input_fd);
		cmd->simplecommand->input_fd = -1;
	}
	cmd->simplecommand->input_fd = open(redir->file, O_RDONLY);
	if (cmd->simplecommand->input_fd < 0)
	{
		perror("Error opening input file");
		msh()->exit_status = 1;
		return (0);
	}
	return (1);
}

static int	handle_output_redir(t_command_table *cmd, t_redirs_list *redir)
{
	int	flags;

	if (cmd->simplecommand->output_fd > 2)
	{
		close(cmd->simplecommand->output_fd);
		cmd->simplecommand->output_fd = -1;
	}
	flags = O_WRONLY | O_CREAT;
	if (redir->redir_type == R_APP)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	cmd->simplecommand->output_fd = open(redir->file, flags, 0644);
	if (cmd->simplecommand->output_fd < 0)
	{
		perror("Error opening output file");
		msh()->exit_status = 1;
		return (0);
	}
	return (1);
}

static void	handle_heredoc_redir(t_command_table *cmd, t_redirs_list *redir)
{
	if (cmd->simplecommand->input_fd > 2)
	{
		close(cmd->simplecommand->input_fd);
		cmd->simplecommand->input_fd = -1;
	}
	run_doc(cmd, redir);
}

static int	handle_in_or_out(t_command_table *current_cmd,
		t_redirs_list *redirs)
{
	if (redirs->redir_type == R_IN)
	{
		if (!handle_input_redir(current_cmd, redirs))
			return (1);
		return (0);
	}
	else if (redirs->redir_type == R_OUT || redirs->redir_type == R_APP)
	{
		if (!handle_output_redir(current_cmd, redirs))
			return (1);
		return (0);
	}
	else
		return (0);
}

int	set_in_and_out(t_command_table *cmd_table)
{
	t_command_table	*current_cmd;
	t_redirs_list	*redirs;

	current_cmd = cmd_table;
	while (current_cmd)
	{
		redirs = current_cmd->redirs;
		while (redirs)
		{
			if (redirs->redir_type == R_IN || (redirs->redir_type == R_OUT
					|| redirs->redir_type == R_APP))
			{
				if (handle_in_or_out(current_cmd, redirs))
					return (1);
			}
			else if (redirs->redir_type == HERE_DOC)
				handle_heredoc_redir(current_cmd, redirs);
			redirs = redirs->next;
		}
		current_cmd = current_cmd->next;
	}
	return (0);
}
