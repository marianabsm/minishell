/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:12:02 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 14:12:03 by marianamest      ###   ########.fr       */
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

void	write_to_pipe(char *str, int fd)
{
	char	*s1;

	s1 = ft_strjoin(str, "\n");
	write(fd, s1, ft_strlen(s1));
	free(s1);
}
