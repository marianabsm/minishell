/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:12:13 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 21:18:36 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	handle_eof(void)
{
	if (!msh()->line)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		prep_next_cmdline(msh());
		return (1);
	}
	return (0);
}

static int	handle_empty_line(void)
{
	if (msh()->line[0] == '\0')
	{
		free(msh()->line);
		return (1);
	}
	return (0);
}

static void	free_exec_struct(void)
{
	if (msh()->exec)
	{
		free(msh()->exec->pid);
		free(msh()->exec);
		msh()->exec = NULL;
	}
}

static int	handle_set_exec(void)
{
	free_exec_struct();
	if (!set_exec())
	{
		free_exec_struct();
		msh()->exit_status = 1;
		return (0);
	}
	return (1);
}

void	msh_loop(char **envp)
{
	init_all(envp);
	while (1)
	{
		main_signals();
		msh()->line = readline("minishell$");
		if (handle_eof())
			break ;
		if (msh()->exit_status == 130)
			msh()->exit_status = 130;
		if (handle_empty_line())
			continue ;
		init_fds();
		add_history(msh()->line);
		signals_ignore();
		if (!handle_parser())
			continue ;
		if (!handle_set_exec())
			continue ;
		start_executing(msh()->exec, msh()->cmd_table);
		reset_fds();
		prep_next_cmdline(msh());
	}
	close(msh()->original_stdout);
	close(msh()->original_stdin);
	free_and_exit(msh());
}
