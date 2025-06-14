/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:19:12 by msilva-c          #+#    #+#             */
/*   Updated: 2025/06/10 23:06:39 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prep_next_cmdline(t_msh *m)
{
	if (!m)
		return ;
	if (m->line)
	{
		free(m->line);
		m->line = NULL;
	}
	if (m->tokens)
	{
		free_tokens(m->tokens);
		m->tokens = NULL;
	}
	if (m->cmd_table)
	{
		close_cmd_table_fds(m->cmd_table);
		free_command_table(m->cmd_table);
		m->cmd_table = NULL;
	}
	if (m->exec)
	{
		free(m->exec->pid);
		free(m->exec);
		m->exec = NULL;
	}
}

void	close_cmd_table_fds(t_command_table *cmd_table)
{
	while (cmd_table)
	{
		if (cmd_table->simplecommand->input_fd > 2)
		{
			close(cmd_table->simplecommand->input_fd);
			cmd_table->simplecommand->input_fd = STDIN_FILENO;
		}
		if (cmd_table->simplecommand->output_fd > 2)
		{
			close(cmd_table->simplecommand->output_fd);
			cmd_table->simplecommand->output_fd = STDOUT_FILENO;
		}
		cmd_table = cmd_table->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	if (ac == 1)
		msh_loop(envp);
	else
		printf("Cmdline to launch: ./minishell\n");
	return (0);
}
