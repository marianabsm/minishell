/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:13:11 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 21:29:34 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	process_tokens_loop(t_token *tokens,
		t_command_table **command_table, t_command_table **new_node)
{
	while (tokens)
	{
		if (tokens->type == PIPE && (!handle_pipe_token(command_table,
					new_node)))
			return (0);
		else if (tokens->type == R_APP || tokens->type == R_IN
			|| tokens->type == R_OUT || tokens->type == HERE_DOC)
			handle_redir_token(*new_node, &tokens);
		else if (tokens->type == CMD)
		{
			if (!handle_cmd_token(*new_node, tokens, command_table))
				return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}

int	process_command(t_command_table **command_table)
{
	t_command_table	*new_node;
	t_token			*tokens;

	new_node = create_cmd_table_node();
	if (!new_node)
		return (0);
	tokens = msh()->tokens;
	if (!process_tokens_loop(tokens, command_table, &new_node))
		return (0);
	if (new_node->simplecommand && new_node->simplecommand->array_args)
		remove_empty_args(new_node->simplecommand->array_args);
	else
		remove_empty_args(NULL);
	if ((new_node->simplecommand && new_node->simplecommand->array_args
			&& new_node->simplecommand->array_args[0]) || new_node->redirs)
		cmd_table_add_back(command_table, new_node);
	else
		free_simplecommand_and_table(new_node);
	return (1);
}
