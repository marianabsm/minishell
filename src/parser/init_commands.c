/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:03:37 by marianamest       #+#    #+#             */
/*   Updated: 2025/05/01 15:01:52 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_simple_command	*init_simple_command(void)
{
	t_simple_command	*simple_command;

	simple_command = (t_simple_command *)malloc(sizeof(t_simple_command));
	if (!simple_command)
		return (NULL);
	simple_command->n_of_arg = 0;
	simple_command->array_args = NULL;
	return (simple_command);
}

t_redirs_list	*init_redirs_list(int type, char *file, char *delimiter)
{
	t_redirs_list	*new;

	new = malloc(sizeof(t_redirs_list));
	if (!new)
		return (NULL);
	new->redir_type = type;
	new->file = NULL;
	if (file)
		new->file = ft_strdup(file);
	new->delimiter = NULL;
	if (delimiter)
		new->delimiter = ft_strdup(delimiter);
	new->heredoc_fd = -1;
	new->expand_heredoc = 0;
	new->next = NULL;
	return (new);
}

t_command_table	*init_cmd_table(int type, char *file, char *delimiter)
{
	t_command_table	*command_table;

	command_table = (t_command_table *)malloc(sizeof(t_command_table));
	if (!command_table)
		return (NULL);
	command_table->shellvl = 0;
	command_table->simplecommand = init_simple_command();
	if (!command_table->simplecommand)
	{
		free(command_table);
		return (NULL);
	}
	command_table->redirs = init_redirs_list(type, file, delimiter);
	command_table->next = NULL;
	if (!command_table->redirs)
	{
		free(command_table->simplecommand);
		free(command_table);
		return (NULL);
	}
	return (command_table);
}
