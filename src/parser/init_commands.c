/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:03:37 by marianamest       #+#    #+#             */
/*   Updated: 2025/05/19 16:45:54 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_simple_command *init_simple_command(void)
{
    t_simple_command *simple_command;

    simple_command = (t_simple_command *)malloc(sizeof(t_simple_command));
    if (!simple_command)
        return (NULL);
    simple_command->name = NULL;
    simple_command->path = NULL;
    simple_command->n_of_arg = 0;
    simple_command->array_args = NULL;
    simple_command->input_fd = STDIN_FILENO;
    simple_command->output_fd = STDOUT_FILENO;
    return (simple_command);
}

t_redirs_list *init_redirs_list_node(t_token **token)
{
    t_redirs_list *new;
    
    new = malloc(sizeof(t_redirs_list));
    if (!new)
        return (NULL);
    new->redir_type = (*token)->type;
    *token = (*token)->next;
    if (new->redir_type != HERE_DOC)
    {
        new->file = ft_strdup((*token)->content);
        new->delimiter = NULL;
    }
    else
    {
        new->file = NULL;
        new->delimiter = ft_strdup((*token)->content);
    }
    new->heredoc_fd = -1;
    new->expand_heredoc = 0;
    new->next = NULL;
    return (new);
}


t_command_table	*init_cmd_table()
{
    t_command_table *command_table;
    
    command_table = (t_command_table *)malloc(sizeof(t_command_table));
    if (!command_table)
        return (NULL);
    command_table->simplecommand = initialize_simple_command();
    if (!command_table->simplecommand)
        return (free(command_table), NULL);
    command_table->redirs = NULL;
    command_table->next = NULL;
    return (command_table);
}
