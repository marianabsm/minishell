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
    if (m->exec)
    {
        i = 0;
        while (i < m->exec->nbr_cmds)
        {
            free_exec(&m->exec[i]);
            i++;
        }
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
			ft_put_str_fd("exit\n", 2);
			break ;
		}
		if(msh()->line)
			add_history(msh()->line);
		if (parser())
		{
			if(!set_exec())
			{
				ft_put_str_fd("Error: Failed to initialize exec\n", 2);
				continue;
			}
			start_executing(msh()->exec, msh()->cmd_table);
		}
		else
		{
			msh()->exit_status = 2;
			free(msh()->line);
		}
		dup2(original_stdin, STDIN_FILENO);
        dup2(original_stdout, STDOUT_FILENO);
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
