/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:02:43 by msilva-c          #+#    #+#             */
/*   Updated: 2025/06/10 21:39:25 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_signaled(int status)
{
	if (WTERMSIG(status) == 2 && !msh()->signaled)
	{
		write(1, "\n", 1);
		msh()->signaled = true;
	}
	else if (WTERMSIG(status) == 3 && !msh()->signaled)
	{
		write(1, "Quit (core dumped)\n", 19);
		msh()->signaled = true;
	}
	msh()->exit_status = 128 + WTERMSIG(status);
}

void	ft_waitpid(int pid)
{
	int	status;

	while (waitpid(pid, &status, 0) == -1)
	{
		if (errno == EINTR)
			continue ;
		perror("waitpid");
		msh()->exit_status = 1;
		return ;
	}
	if (WIFEXITED(status))
		msh()->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		handle_signaled(status);
	else
		msh()->exit_status = 1;
}

void	signals_parent(void)
{
	signal(SIGINT, SIG_IGN);
}

void	signals_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
