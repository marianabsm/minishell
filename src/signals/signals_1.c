/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 01:16:49 by msilva-c          #+#    #+#             */
/*   Updated: 2025/06/10 21:39:33 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigquit_handler(int sig)
{
	(void)sig;
	write(1, "Quit (core dumped)\n", 19);
	free_and_exit(msh());
	exit(131);
}

void	sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	msh()->exit_status = 130;
}

void	main_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}

void	is_a_dir(const char *exec_path)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *)exec_path, STDERR_FILENO);
	ft_putstr_fd(": is a directory\n", STDERR_FILENO);
	msh()->exit_status = 126;
}

void	perm_den(const char *fail_path)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *)fail_path, STDERR_FILENO);
	ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	msh()->exit_status = 126;
}
