/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_call_error_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:42:43 by msilva-c          #+#    #+#             */
/*   Updated: 2025/03/20 21:56:51 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_check_access(char *str, char *cmd, char **tmp)
{
	cmd = ft_strjoin(str, cmd);
	free(str);
	if (!access(cmd, F_OK) && !access(cmd, R_OK))
	{
		tmp[0] = cmd;
		return 1;
	}
	free(cmd);
	return 0;
}
