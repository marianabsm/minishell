/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrito- <mabrito-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:20:32 by marianamest       #+#    #+#             */
/*   Updated: 2025/04/02 19:21:49 by mabrito-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_redirection(const char *token)
{
    if (strcmp(token, "|") == 0 )
        return (1);
    return (0);
}

static int	count_args_for_command(char **tokens, int token_count, int *token_index)
{
    int	arg_count;

    arg_count = 0;
    while (*token_index < token_count && !is_redirection(tokens[*token_index]))
    {
        arg_count++;
        (*token_index)++;
    }
    return (arg_count);
}

static int	copy_args_to_command(t_simple_command *cmd, char **tokens, int start_token, int arg_count)
{
    int	arg_pos;

    cmd->n_of_arg = arg_count;
    cmd->array_args = malloc((arg_count + 1) * sizeof(char *));
    if (!cmd->array_args)
    {
        fprintf(stderr, "Error: Memory allocation failed for command arguments.\n");
        return (0);
    }
    arg_pos = 0;
    while (arg_pos < arg_count)
    {
        cmd->array_args[arg_pos] = strdup(tokens[start_token + arg_pos]);
        if (!cmd->array_args[arg_pos])
        {
            fprintf(stderr, "Error: Memory allocation failed for argument duplication.\n");
            while (arg_pos-- > 0)
                free(cmd->array_args[arg_pos]);
            free(cmd->array_args);
            return (0);
        }
        arg_pos++;
    }
    cmd->array_args[arg_count] = NULL;
    return (1);
}
static int  count_command_sections(char **tokens, int token_count)
{
    int section_count;
    int i;

    section_count = 0;
    i = 0;
    while (i < token_count)
    {
        while (i < token_count && is_redirection(tokens[i]))
            i++;
        if (i < token_count && !is_redirection(tokens[i]))
        {
            section_count++;
            while (i < token_count && !is_redirection(tokens[i]))
                i++;
        }
    }
    return (section_count);
}

t_simple_command	*split_commands_into_structs(char **tokens, int token_count, int *n_commands)
{
    t_simple_command	*cmds;
    int					cmd_index;
    int					token_index;
    int					start_token;
    int					arg_count;

    *n_commands = count_command_sections(tokens, token_count);
    if (*n_commands <= 0)
    {
        fprintf(stderr, "Error: No commands found.\n");
        return (NULL);
    }
    cmds = malloc(*n_commands * sizeof(t_simple_command));
    if (!cmds)
    {
        fprintf(stderr, "Error: Memory allocation failed for command structs.\n");
        return (NULL);
    }
    cmd_index = 0;
    token_index = 0;
    while (cmd_index < *n_commands)
    {
        start_token = token_index;
        arg_count = count_args_for_command(tokens, token_count, &token_index);
        if (!copy_args_to_command(&cmds[cmd_index], tokens, start_token, arg_count))
        {
            free_command_structs(cmds, cmd_index);
            return (NULL);
        }
        if (token_index < token_count && is_redirection(tokens[token_index]))
            token_index++;
        cmd_index++;
    }
    return (cmds);
}

void	free_command_structs(t_simple_command *cmds, int n_commands)
{
    int	cmd_idx;
    int	arg_idx;

    if (!cmds)
        return;
    cmd_idx = 0;
    while (cmd_idx < n_commands)
    {
        arg_idx = 0;
        while (arg_idx < cmds[cmd_idx].n_of_arg)
        {
            free(cmds[cmd_idx].array_args[arg_idx]);
            arg_idx++;
        }
        free(cmds[cmd_idx].array_args);
        cmd_idx++;
    }
    free(cmds);
}