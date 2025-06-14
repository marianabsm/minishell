/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 06:32:58 by msilva-c          #+#    #+#             */
/*   Updated: 2025/06/10 21:39:49 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	handle_split_line_errors(char **split_line)
{
	if (split_line[0] && ft_strcmp(split_line[0], "$?") == 0
		&& split_line[1] == NULL)
	{
		ft_putstr_fd("minishell: $?: command not found\n", STDERR_FILENO);
		msh()->exit_status = 127;
		free_matrix(split_line);
		return (0);
	}
	return (1);
}

static int	handle_parser_tokens(char **split_line)
{
	if (!parser_tokens(split_line))
	{
		if (msh()->tokens)
		{
			free_tokens(msh()->tokens);
			msh()->tokens = NULL;
		}
		free_matrix(split_line);
		return (0);
	}
	return (1);
}

static int	handle_syntax_and_expand(void)
{
	if (!parser_syntax_and_expand())
	{
		if (msh()->tokens)
		{
			free_tokens(msh()->tokens);
			msh()->tokens = NULL;
		}
		return (0);
	}
	return (1);
}

static int	handle_process_command(t_command_table **command_table)
{
	if (!parser_process_command(command_table) || *command_table == NULL)
	{
		if (msh()->tokens)
		{
			free_tokens(msh()->tokens);
			msh()->tokens = NULL;
		}
		if (*command_table)
			free_command_table(*command_table);
		msh()->exit_status = 0;
		return (0);
	}
	return (1);
}

int	parser(void)
{
	char			*new_line;
	char			**split_line;
	t_command_table	*command_table;

	command_table = NULL;
	new_line = parser_add_spaces();
	if (!new_line)
		return (0);
	split_line = parser_split_line(new_line);
	if (!split_line)
		return (msh()->exit_status);
	if (!handle_split_line_errors(split_line))
		return (0);
	if (!handle_parser_tokens(split_line))
		return (0);
	free_matrix(split_line);
	if (!handle_syntax_and_expand())
		return (0);
	if (!handle_process_command(&command_table))
		return (0);
	help_parser(command_table);
	return (1);
}
