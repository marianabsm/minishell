/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:07:40 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 20:23:06 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_flag_n(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
	{
		i++;
		while (str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}

void	print_args(char **args, int start_index, int fd)
{
	int	i;

	i = start_index;
	while (args[i])
	{
		write(fd, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(fd, " ", 1);
		i++;
	}
}

void	run_echo(char **args, int fd)
{
	int	start_index;
	int	newline;

	start_index = 1;
	newline = 1;
	while (args[start_index] && is_flag_n(args[start_index]))
	{
		newline = 0;
		start_index++;
	}
	print_args(args, start_index, fd);
	if (newline)
		write(fd, "\n", 1);
}
