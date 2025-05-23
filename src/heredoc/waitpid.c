/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitpid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrito- <mabrito-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:22:09 by marianamest       #+#    #+#             */
/*   Updated: 2025/03/27 16:22:26 by mabrito-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_pipe(int *fd)
{
	safe_close(fd[0]);
	safe_close(fd[1]);
}

void	safe_close(int fd)
{
	if (fd > 2)
		close(fd);
}

void	write_to_pipe(char *str, t_exec *exec)
{
	char	*s1;

	s1 = ft_strjoin(str, "\n");
	write(exec->pipe_fd[1], s1, ft_strlen(str));
	free(s1);
}
