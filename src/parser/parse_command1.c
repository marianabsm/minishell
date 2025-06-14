/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:20:32 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/09 22:06:10 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	final_info(t_simple_command **cmd, char **cmd_arr)
{
	free_matrix((*cmd)->array_args);
	(*cmd)->array_args = cmd_arr;
	remove_empty_args((*cmd)->array_args);
	if ((*cmd)->name)
		free((*cmd)->name);
	if ((*cmd)->array_args[0])
		(*cmd)->name = ft_strdup((*cmd)->array_args[0]);
	else
		(*cmd)->name = NULL;
}

static char	**copy_old_args(char **old_args, int n_of_arg)
{
	char	**cmd_arr;
	int		i;

	cmd_arr = malloc(sizeof(char *) * (n_of_arg + 1));
	if (!cmd_arr)
		return (NULL);
	i = -1;
	while (++i < n_of_arg - 1)
	{
		cmd_arr[i] = ft_strdup(old_args[i]);
		if (!cmd_arr[i])
		{
			while (--i >= 0)
				free(cmd_arr[i]);
			free(cmd_arr);
			return (NULL);
		}
	}
	return (cmd_arr);
}

static void	free_cmd_arr(char **cmd_arr, int last)
{
	while (--last >= 0)
		free(cmd_arr[last]);
	free(cmd_arr);
}

void	add_cmd_info(t_simple_command **cmd, t_token *token)
{
	char	**cmd_arr;
	int		i;

	(*cmd)->n_of_arg++;
	cmd_arr = copy_old_args((*cmd)->array_args, (*cmd)->n_of_arg);
	if (!cmd_arr)
		return ;
	i = (*cmd)->n_of_arg - 1;
	cmd_arr[i] = ft_strdup(token->content);
	if (!cmd_arr[i])
	{
		free_cmd_arr(cmd_arr, i);
		return ;
	}
	cmd_arr[++i] = NULL;
	final_info(cmd, cmd_arr);
}
