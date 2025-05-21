/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_executer_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:59:02 by msilva-c          #+#    #+#             */
/*   Updated: 2025/05/21 13:06:55 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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