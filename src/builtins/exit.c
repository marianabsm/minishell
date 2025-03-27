/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:35:26 by marianamest       #+#    #+#             */
/*   Updated: 2025/03/22 21:00:25 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exit_format_error(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[0] == '+' || cmd[0] == '-')
		i++;
	while (cmd[i])
	{
		if (!ft_isdigit(cmd[i]))
			return (1);
		i++;
	}
	return (0);
}

int	normalize_exit_code(int code)
{
	return ((code % 256 + 256) % 256);
}

void	exit_error(char *arg)
{
	write(2, "exit\nerror: exit: ", 18);
	write(2, arg, ft_strlen(arg));
	write(2, ": numeric argument required\n", 28);
}

void	exec_exit(char **args)
{
	int	exit_code;

	exit_code = 0;
	if (args[1] && args[2])
	{
		write(2, "exit: too many arguments\n", 25);
		exit(1);
	}
	else if (args[1])
	{
		if (exit_format_error(args[1]))
		{
			exit_error(args[1]);
			exit(2);
		}
		exit_code = normalize_exit_code(ft_atoi(args[1]));
	}
	write(1, "exit\n", 5);
	//FAZER FREE ALL
	exit(exit_code);
}
