/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:36:18 by msilva-c          #+#    #+#             */
/*   Updated: 2025/05/21 13:21:08 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int size_args(char **args)
{
	int size;

	size = 0;
	if (!args || !args[0])
		return (0);
	while(args[size])
		size++;
	return size;
}

char **exred(char **args, int i)
{
	char **new;
	int size;
	int	j;
	int	k;

	size = size_args(args);
	new = safe_malloc((size + 1) * sizeof(char *));
	j = 0;
	k = 0;
	while(k < size && args[k])
	{
		if (k == i)
			k += 2;
		else
			new[j++] = args[k++];
	}
	return (new);
}

int exec_r(t_exec *ex, char *value)
{
    safe_close(ex->out_fd);
    ex->out_fd = open(value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (ex->out_fd < 0)
        return (0);
    if (dup2(ex->out_fd, STDOUT_FILENO) < 0)
    {
        perror("dup2 failed");
        return (0);
    }
    return (1);
}

int exec_rr(t_exec *ex, char *value)
{
    safe_close(ex->out_fd);
    ex->out_fd = open(value, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (ex->out_fd < 0)
        return (0);
    if (dup2(ex->out_fd, STDOUT_FILENO) < 0)
    {
        perror("dup2 failed");
        return (0);
    }
    return (1);
}
