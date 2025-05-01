/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 01:38:25 by msilva-c          #+#    #+#             */
/*   Updated: 2025/05/01 15:02:42 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_and_exit(t_msh *m)
{
	int	i;

	if (!m)
		return ;
	clear_history();
	if (m->line)
		free(m->line);
	if (m->home)
		free(m->home);
	if (m->pwd)
		free(m->pwd);
	if (m->env)
		free_env(m->env);
	if (m->tokens)
		free_tokens(m->tokens);
	if (m->exec)
	{
		i = 0;
		while (i < m->exec->nbr_cmds)
			free_exec(&m->exec[i++]);
		free(m->exec);
	}
}
