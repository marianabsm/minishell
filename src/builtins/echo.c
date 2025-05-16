/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:07:40 by marianamest       #+#    #+#             */
/*   Updated: 2025/03/21 18:20:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_flag_n(char *str) // protects from -n flag
{
	return (str[0] == '-' && str[1] == 'n' && str[2] == '\0');
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
