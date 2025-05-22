/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 01:38:25 by msilva-c          #+#    #+#             */
/*   Updated: 2025/03/22 13:06:27 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_and_exit(t_msh *m)
{
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
		free(m->exec->pid);
		free(m->exec);
	}
}
