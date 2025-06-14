/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:13:18 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 19:31:51 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_command_table	*create_cmd_table_node(void)
{
	t_command_table	*new_table;

	new_table = init_cmd_table();
	if (!new_table)
		return (NULL);
	return (new_table);
}

int	handle_pipe_token(t_command_table **command_table,
		t_command_table **new_node)
{
	cmd_table_add_back(command_table, *new_node);
	*new_node = create_cmd_table_node();
	if (!*new_node)
		return (0);
	return (1);
}

int	handle_redir_token(t_command_table *new_node, t_token **tokens)
{
	add_redir(&(new_node->redirs), init_redirs_list_node(tokens));
	return (1);
}

int	handle_cmd_token(t_command_table *new_node, t_token *token,
		t_command_table **command_table)
{
	add_cmd_info(&(new_node->simplecommand), token);
	if (!new_node->simplecommand->array_args)
	{
		free_simplecommand_and_table(new_node);
		free_command_table(*command_table);
		return (0);
	}
	return (1);
}
