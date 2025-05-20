/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 19:20:02 by msilva-c          #+#    #+#             */
/*   Updated: 2025/05/20 14:18:26 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_struct(t_token **lst_head)
{
	t_token	*current;
	t_token	*counter;
	int		i;

	current = *lst_head;
	counter = *lst_head;
	i = 0;
	while (counter)
	{
		i++;
		counter = counter->next;
	}
	printf("has %d nodes\n", i);
	while (current)
	{
		printf("node: %p\n", current);
		if (current->content != NULL)
			printf("content: %s$ type: %d\n", current->content, current->type);
		else
			printf("content: (null)$\n");
		current = current->next;
	}
}

void print_exec(t_exec *exec)
{
    int i;

    if (!exec)
    {
        printf("t_exec is NULL\n");
        return;
    }

    printf("t_exec Debug Info:\n");
    printf("pid: %d\n", exec->pid);
    printf("nbr_cmds: %d\n", exec->nbr_cmds);
    printf("pipe_fd: [%d, %d]\n", exec->pipe_fd[0], exec->pipe_fd[1]);
    printf("pipe_doc: [%d, %d]\n", exec->pipe_doc[0], exec->pipe_doc[1]);
    printf("in_fd: %d\n", exec->in_fd);
    printf("out_fd: %d\n", exec->out_fd);
    printf("is_heredoc: %s\n", exec->is_heredoc ? "true" : "false");
    printf("cmd_invalid: %s\n", exec->cmd_invalid ? "true" : "false");
    printf("index: %d\n", exec->index);

    printf("args:\n");
    if (exec->args)
    {
        i = 0;
        while (exec->args[i])
        {
            printf("  args[%d]: %s\n", i, exec->args[i]);
            i++;
        }
    }
    else
    {
        printf("  args is NULL\n");
    }

    printf("envp:\n");
    if (exec->envp)
    {
        i = 0;
        while (exec->envp[i])
        {
            printf("  envp[%d]: %s\n", i, exec->envp[i]);
            i++;
        }
    }
    else
    {
        printf("  envp is NULL\n");
    }
}
