/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:03:37 by marianamest       #+#    #+#             */
/*   Updated: 2025/04/02 21:56:13 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_simple_command *init_simple_command(void)
{
    t_simple_command *simple_command;

    simple_command = (t_simple_command *)malloc(sizeof(t_simple_command));
    if (!simple_command)
        return (NULL);
    simple_command->n_of_arg = 0;
    simple_command->array_args = NULL;
    return (simple_command);
}

t_redirs_list *init_redirs_list(void)
{
    t_redirs_list *redirs;

    redirs = (t_redirs_list *)malloc(sizeof(t_redirs_list));
    if (!redirs)
        return (NULL);
    redirs->redir_type = 0;
    redirs->file = NULL;
    redirs->delimiter = NULL;
    redirs->heredoc_fd = -1;
    redirs->expand_heredoc = 0;
    return (redirs);
}

t_command_table	*init_cmd_table(void)
{
    t_command_table *command_table;
    
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
    command_table->redirs = init_redirs_list();
    if (!command_table->redirs)
    {
        free(command_table->simplecommand);
        free(command_table);
        return (NULL);
    }
    return (command_table); 
}
