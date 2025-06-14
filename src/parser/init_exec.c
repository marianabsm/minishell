/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:08:55 by msilva-c          #+#    #+#             */
/*   Updated: 2025/06/08 20:24:57 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_cmds(void)
{
	t_command_table	*tmp;
	int				nbr_cmds;

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
	int	i;

	i = 0;
	if (args)
	{
		while (args[i])
			i++;
	}
	return (i);
}

char	**add_to_matrix(char *content, char **args)
{
	int		i;
	char	**new;

	i = 0;
	new = safe_malloc(sizeof(char *) * (strlen_args(args) + 2));
	while (args && args[i])
	{
		new[i] = ft_strdup(args[i]);
		i++;
	}
	new[i] = ft_strdup(content);
	if (!new[i])
	{
		while (i-- > 0)
			free(new[i]);
		free(new);
		if (args)
			free_matrix(args);
		return (NULL);
	}
	new[++i] = NULL;
	if (args)
		free_matrix(args);
	return (new);
}

t_exec	*init_exec(void)
{
	t_exec	*exec;

	exec = (t_exec *)malloc(sizeof(t_exec));
	if (!exec)
	{
		ft_putstr_fd(MALLOC_FAIL, STDERR_FILENO);
		return (NULL);
	}
	exec->nbr_cmds = count_cmds();
	exec->pid = malloc(sizeof(pid_t) * exec->nbr_cmds);
	if (!exec->pid)
	{
		ft_putstr_fd(MALLOC_FAIL, STDERR_FILENO);
		free(exec);
		return (NULL);
	}
	exec->index = 0;
	exec->out_pipe_fd[1] = -1;
	exec->out_pipe_fd[0] = exec->out_pipe_fd[1];
	exec->in_pipe_fd[1] = -1;
	exec->in_pipe_fd[0] = exec->in_pipe_fd[1];
	return (exec);
}

int	set_exec(void)
{
	msh()->exec = init_exec();
	if (!msh()->exec)
		return (0);
	return (1);
}
