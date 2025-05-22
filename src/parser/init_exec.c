/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:08:55 by msilva-c          #+#    #+#             */
/*   Updated: 2025/05/21 14:15:26 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_cmds(void)
{
    t_command_table *tmp;
	int             nbr_cmds;

    tmp = msh()->cmd_table;
	nbr_cmds = 0;
	while (tmp)
	{
		nbr_cmds++;
		tmp = tmp->next;
	}
	return (nbr_cmds);
}

int	strlen_args(char **args)
{
	int i = 0;
	if (args)
	{
		while (args[i])
			i++;
	}
	return i;
}
char **add_to_matrix(char *content, char **args)
{
    int i = 0;
    int new_size = strlen_args(args) + 2; // +1 for new string, +1 for NULL
    char **new = safe_malloc(sizeof(char *) * new_size);

    while (args && args[i])
    {
        new[i] = args[i]; // Reuse existing pointers
        i++;
    }
    new[i++] = ft_strdup(content);
    new[i] = NULL;
    free(args); // Free the old matrix
    return (new);
}

t_exec *init_exec(void)
{
    t_exec *exec;

    exec = (t_exec *)malloc(sizeof(t_exec));
    if (!exec)
    {
        ft_putstr_fd("Error: Memory allocation failed in init_exec\n", STDERR_FILENO);
        return (NULL);
    }
    exec->nbr_cmds = count_cmds();
    exec->pid = malloc(sizeof(pid_t) * exec->nbr_cmds);
    if (!exec->pid)
    {
        ft_putstr_fd("Error: Memory allocation failed in init_exec\n", STDERR_FILENO);
        return (NULL);
    }
    exec->index = 0;
    exec->out_pipe_fd[0] = -1;
    exec->out_pipe_fd[1] = -1;
    exec->in_pipe_fd[0] = -1;
    exec->in_pipe_fd[1] = -1;
    return (exec);
}

int set_exec(void)
{
    msh()->exec = init_exec();
    if (!msh()->exec)
    {
        ft_putstr_fd("Error: init_exec failed in set_exec\n", STDERR_FILENO);
        return (0);
    }
    return (1);
}