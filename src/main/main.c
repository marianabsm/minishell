/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:19:12 by msilva-c          #+#    #+#             */
/*   Updated: 2025/03/22 13:33:38 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    prep_next_cmdline(t_msh *m)
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
	if (m->exec)
	{
		int i = 0;

		while (i < m->exec->nbr_cmds)
			free_exec(&m->exec[i++]);
		m->exec = NULL;
	}
}

void	msh_loop(char **envp)
{
    init_all(envp);
    while (1)
    {
		msh()->line = readline("minishell$");
        if (!msh()->line)
        {
            ft_put_str_fd("exit\n", 2);
            break ;
        }
        if (msh()->line && *msh()->line)
        {
            add_history(msh()->line);
            if (parser())
				start_executing();
            else
                msh()->exit_status = 2;
        }
        prep_next_cmdline(msh());
    }
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
