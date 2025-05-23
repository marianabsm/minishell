/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 06:32:58 by msilva-c          #+#    #+#             */
/*   Updated: 2025/05/21 14:15:29 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void set_in_and_out(t_command_table *cmd_table)
{
    t_command_table *current_cmd;
    t_redirs_list   *redirs;

    current_cmd = cmd_table;
    while (current_cmd)
    {
        redirs = current_cmd->redirs;
        while (redirs)
        {
            if (redirs->redir_type == R_IN)
            {
                if (current_cmd->simplecommand->input_fd > 0)
                    close(current_cmd->simplecommand->input_fd); // Close previous input_fd
                current_cmd->simplecommand->input_fd = open(redirs->file, O_RDONLY);
                if (current_cmd->simplecommand->input_fd < 0)
                {
                    perror("Error opening input file");
                    return ;
                }
            }
            else if (redirs->redir_type == R_OUT || redirs->redir_type == R_APP)
            {
                if (current_cmd->simplecommand->output_fd > 1)
                    close(current_cmd->simplecommand->output_fd);
                int flags = O_WRONLY | O_CREAT;
                if (redirs->redir_type == R_APP)
                    flags |= O_APPEND;
                else
                    flags |= O_TRUNC;
                current_cmd->simplecommand->output_fd = open(redirs->file, flags, 0644);
                if (current_cmd->simplecommand->output_fd < 0)
                {
                    perror("Error opening output file");
                    return ;
                }
            }
            redirs = redirs->next;
        }
        current_cmd = current_cmd->next;
    }
}

int ft_compare(char **split_line, int i)
{
    if (ft_strcmp(split_line[i], "<") == 0 || ft_strcmp(split_line[i], ">") == 0 ||
        ft_strcmp(split_line[i], ">>") == 0 || ft_strcmp(split_line[i], "<<") == 0)
        return (1);
    return (0);
}

static void cmd_table_add_back(t_command_table **table, t_command_table *new_node)
{
    t_command_table *tmp;

    tmp = *table;
	if (!tmp)
	{
		*table = new_node;
		return;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

// Function to initialize and validate the command table
static t_command_table *create_cmd_table_node(void)
{
    t_command_table *new_table;

    new_table = init_cmd_table();
    if (!new_table)
    {
        ft_putstr_fd("Error: Failed to initialize command table.\n", STDERR_FILENO);
        return (NULL);
    }
    return (new_table);
}

// Function to initialize and validate the simple command
t_simple_command *initialize_simple_command(void)
{
    t_simple_command *new_table;

    new_table = init_simple_command();
    if (!new_table)
    {
        ft_putstr_fd("Error: Failed to initialize simple command.\n", STDERR_FILENO);
        return (NULL);
    }
    return (new_table);
}

// // Function to parse arguments for a simple command
// static int parse_arguments(char **split_line, int start_token, int token_count, t_simple_command *simple_command)
// {
//     int arg_count;
//     int arg_index;
//     int i;
    
//     arg_count = token_count - start_token;
//     simple_command->array_args = malloc((arg_count + 1) * sizeof(char *));
//     if (!simple_command->array_args)
//     {
//         ft_putstr_fd("Error: Memory allocation failed for arguments.\n", STDERR_FILENO);
//         return (0);
//     }
//     arg_index = 0;
//     i = start_token;
//     while (i < token_count)
//     {
//         if (!ft_compare(split_line, i))
//             simple_command->array_args[arg_index++] = ft_strdup(split_line[i]);
//         i++;
//     }
//     simple_command->array_args[arg_index] = NULL;
//     simple_command->n_of_arg = arg_index;
//     simple_command->name = ft_strdup(simple_command->array_args[0]);
//     return (1);
// }

// Function to process a single command
// static int process_command(char **split_line, int *token_count, t_command_table **command_table, t_command_table **current_table)
// {
//     int start_token;
//     int arg_count;
//     t_redirs_list *redirs_list;
//     t_command_table *new_table;
//     t_simple_command *simple_command;

//     redirs_list = NULL;
//     new_table = create_cmd_table_node(&redirs_list);
//     parse_redirections(split_line + *token_count, &redirs_list);
//     if (!new_table)
//         return (0);
//     simple_command = initialize_simple_command(new_table);
//     if (!simple_command)
//         return (0);
//     start_token = *token_count;
//     arg_count = 0;
//     while (split_line[*token_count] && ft_strcmp(split_line[*token_count], "|") != 0)
//     {
//         if (ft_compare(split_line, *token_count))
//             *token_count += 2;
//         else
//         {
//             arg_count++;
//             (*token_count)++;
//         }
//     }
//     if (!parse_arguments(split_line, start_token, *token_count, simple_command))
//     {
//         free_redirs_list(new_table->redirs);
//         free(new_table);
//         free(simple_command);
//         return (0);
//     }
//     new_table->simplecommand = simple_command;
//     if (!*command_table)
//         *command_table = new_table;
//     else
//         (*current_table)->next = new_table;
//     *current_table = new_table;

//     if (split_line[*token_count] && ft_strcmp(split_line[*token_count], "|") == 0)
//         (*token_count)++;
//     return (1);
// }


//// Function to handle tokens and count arguments
//static int handle_tokens_and_count_args(char **split_line, int *token_count, int *arg_count)
//{
//    int start_token = *token_count;
//    *arg_count = 0;
//
//    while (split_line[*token_count] && ft_strcmp(split_line[*token_count], "|") != 0)
//    {
//        if (ft_compare(split_line, *token_count))
//            *token_count += 2;
//        else
//        {
//            (*arg_count)++;
//            (*token_count)++;
//        }
//    }
//
//    return start_token;
//}
//
//// Function to create and link the command table
//static int create_and_link_command_table(char **split_line, int start_token, int token_count, 
//                                         t_command_table **command_table, t_command_table **current_table, 
//                                         t_command_table *new_table, t_simple_command *simple_command)
//{
//    if (!parse_arguments(split_line, start_token, token_count, simple_command))
//    {
//        free_redirs_list(new_table->redirs);
//        free(new_table);
//        free(simple_command);
//        return (0);
//    }
//    new_table->simplecommand = simple_command;
//    if (!*command_table)
//        *command_table = new_table;
//    else
//        (*current_table)->next = new_table;
//    *current_table = new_table;
//    return (1);
//}

// Refactored process_command function
static int process_command(t_command_table **command_table)
{
    t_command_table *new_node;
    t_token         *tokens;

    new_node = create_cmd_table_node();
    if (!new_node)
        return (0);
    tokens = msh()->tokens;
    while (tokens)
    {
        if (tokens->type == PIPE)
        {
            cmd_table_add_back(command_table, new_node);
            new_node = create_cmd_table_node();
            if (!new_node)
                return (0);
        }
        else if (tokens->type == R_APP || tokens->type == R_IN
            || tokens->type == R_OUT || tokens->type == HERE_DOC)
            add_redir(&(new_node->redirs), init_redirs_list_node(&tokens));
        else if (tokens->type == CMD)
            add_cmd_info(&(new_node->simplecommand), tokens);
        tokens = tokens->next;
    }
    cmd_table_add_back(command_table, new_node);
    return (1);
}

int parser(void)
{
    char *new_line;
    char **split_line;
    t_command_table *command_table;

    command_table = NULL;
    new_line = add_spaces(msh()->line);
    if (!new_line)
        return (0);
    split_line = split_by_spaces(new_line);
    if (!split_line)
        return (0);
    msh()->tokens = matrix_to_tokens(split_line);
    if (!msh()->tokens)
        return (ft_putstr_fd("Error: Tokens not initialized in parser\n", STDERR_FILENO), 0);
    free_matrix(split_line);
    if (!check_syntax_general(msh()->tokens))
        return (0);
    if (!process_command(&command_table))
        return (0);
    free_tokens(msh()->tokens);
    msh()->tokens = NULL;
    msh()->cmd_table = command_table;
    print_msh(msh());
    set_in_and_out(msh()->cmd_table);
    return (1);
}
