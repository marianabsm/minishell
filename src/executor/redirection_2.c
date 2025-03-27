/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:36:18 by msilva-c          #+#    #+#             */
/*   Updated: 2025/03/22 10:11:44 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int exec_l(t_exec *ex, char *value)
{
	safe_close(ex->out_fd);
	ex->out_fd = open(value, O_RDONLY);
	if (ex->out_fd < 0)
		return (0);
	return (1);
}

int exec_red2(t_exec *ex, char *key, char *value)
{
	int ret;

	ret = 0;
	if (!ft_strncmp(key, ">", 1))
		ret = exec_r(ex, value);
	else if (!ft_strncmp(key, "<", 1))
		ret = exec_l(ex, value);
	else if (!strncmp(key, ">>", 2))
		ret = exec_rr(ex, value);
	return (ret);
}

char **exec_red(t_exec *ex, int ex_index)
{
	char **args;
	int i = 0;

	args = ex->args;
	if (doc_loop(args, ex, ex_index) < 0)
			return (NULL);
	while (args && args[i])
	{
		if (!ft_strncmp(args[i], ">>", 2) || !ft_strncmp(args[i], ">", 1) || !ft_strncmp(args[i], "<", 1))
		{
			if (!exec_red2(ex, args[i], args[i + 1]))
				return (NULL);
			args = exred(args, i);
			i = 0;
		}
		else
			i++;
	}
	return (args);
}

int	check_redirs(t_exec *ex)
{
	char 	**temp;
	int ex_index = 0;
	while (ex_index < msh()->exec->nbr_cmds)
	{
		temp = exec_red(&ex[ex_index], ex_index);
		if (!temp)
			return (0);
		//free_matrix(ex[ex_index].args);
		ex[ex_index].args = temp;
		ex_index++;
	}
	return (1);
}
