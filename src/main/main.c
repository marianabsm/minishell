/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:19:12 by msilva-c          #+#    #+#             */
/*   Updated: 2025/05/21 14:11:07 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prep_next_cmdline(t_msh *m)
{
    int i;
	
    if (!m)
        return;
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

void	msh_loop(char **envp)
{
	int original_stdin = dup(STDIN_FILENO);
    int original_stdout = dup(STDOUT_FILENO);
	init_all(envp);
	while (1)
	{
		msh()->line = readline("minishell$");
		if (!msh()->line)
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			break ;
		}
		if(msh()->line)
			add_history(msh()->line);
		if (parser())
		{
			if(!set_exec())
			{
				ft_putstr_fd("Error: Failed to initialize exec\n", STDERR_FILENO);
				continue;
			}
			start_executing(msh()->exec, msh()->cmd_table);
		}
		else
		{
			msh()->exit_status = 2;
			prep_next_cmdline(msh());
			continue ;
		}
		prep_next_cmdline(msh());
	}
	close(original_stdin);
    close(original_stdout);
	free_and_exit(msh());
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	if (ac == 1)
	{
		main_signals();
		msh_loop(envp);
	}
	else
		printf("Cmdline to launch: ./minishell\n");
	return (0);
}
