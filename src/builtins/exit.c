/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:35:26 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 18:25:25 by gcapa-pe         ###   ########.fr       */
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

void	exit_error(char *arg)
{
	write(2, "exit\nerror: exit: ", 18);
	write(2, arg, ft_strlen(arg));
	write(2, ": numeric argument required\n", 28);
}

static void	exit_error_helper(char *arg)
{
	ft_putstr_fd("exit\nerror: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

static void	exit_error_helper2(void)
{
	ft_putstr_fd("exit: too many arguments\n", 2);
	msh()->exit_status = 1;
}

void	exec_exit(char **args)
{
	int			exit_code;
	char		*endptr;
	long long	val;

	exit_code = 0;
	if (args[1] && args[2])
	{
		exit_error_helper2();
		return ;
	}
	else if (args[1])
	{
		errno = 0;
		val = ft_strtoll(args[1], &endptr, 10);
		if (errno == ERANGE || *endptr != '\0' || val > LLONG_MAX
			|| val < LLONG_MIN)
		{
			exit_error_helper(args[1]);
			exit(2);
		}
		exit_code = normalize_exit_code((int)val);
	}
	free_and_exit(msh());
	exit(exit_code);
}
