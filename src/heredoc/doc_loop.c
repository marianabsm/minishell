/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:29:52 by marianamest       #+#    #+#             */
/*   Updated: 2025/03/22 15:38:08 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



int	doc_loop(char **args, t_exec *exec, int ex_index) // rever :  doc pipe checex_index
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		if (!ft_strncmp(args[i], "<<", 2))
		{
			safe_close(exec[ex_index].pipe_fd[0]);
			if (run_doc(args[i + 1], exec, ex_index) < 0)
				return (-1);
		}
		i++;
	}
	if (!is_final_heredoc(args, exec, ex_index))
		safe_close(exec[ex_index].pipe_fd[0]);
	return (0);
}


int	open_infile_loop(char **in_redirs, t_exec *exec, int k)
{
	int	i;

	i = 0;
	while (in_redirs[i] != NULL)
	{
		if (ft_strncmp(in_redirs[i], "<<", 2) != 0)
			if (!check_and_open_file(in_redirs[i + 1]))
				exec[k].cmd_invalid = true;
	}
	if (exec[k].is_heredoc)
		safe_close(exec->in_fd);
	return (0);
}

int	is_final_heredoc(char **in_redirs, t_exec *exec, int k)
{
	int	i;
	int	last_heredoc_index;

	last_heredoc_index = -1;
	i = 0;
	while (in_redirs[i] != NULL)
	{
		if (ft_strncmp(in_redirs[i], "<<", 2) == 0)
		{
			last_heredoc_index = i;
		}
		i++;
	}
	if (last_heredoc_index != -1 && last_heredoc_index == i - 1)
	{
		exec[k].is_heredoc = true;
		return (1);
	}
	exec[k].is_heredoc = false;
	return (0);
}

bool	check_and_open_file(char *file_name)
{
	int	fd;

	if (file_name == NULL || *file_name == '\0')
	{
		ft_put_str_fd("Error: File name is empty\n", STDERR_FILENO);
		return (false);
	}
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		ft_put_str_fd("Error opening file: %s\n", STDERR_FILENO);
		return (false);
	}
	safe_close(fd);
	return (true);
}
