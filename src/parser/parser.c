/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 06:32:58 by msilva-c          #+#    #+#             */
/*   Updated: 2025/05/20 15:33:27 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void print_msh(t_msh *msh)
{
    t_token *token;

    if (!msh)
    {
        printf("msh is NULL\n");
        return;
    }
    printf("msh->line: %s\n", msh->line ? msh->line : "(NULL)");
    printf("msh->home: %s\n", msh->home ? msh->home : "(NULL)");
    printf("msh->pwd: %s\n", msh->pwd ? msh->pwd : "(NULL)");
    printf("msh->env: %p\n", (void *)msh->env);
    printf("msh->exec: %p\n", (void *)msh->exec);
    printf("msh->exit: %d\n", msh->exit_status);
    printf("Tokens:\n");
    token = msh->tokens;
    if (!token)
        printf("(NULL)\n");
    while (token)
    {
        printf("  Token content: %s\n", token->content ? token->content : "(NULL)");
        printf("  Token type: %d\n", token->type);
        printf("  Token index: %d\n", token->index);
        printf("  Token prev: %p\n", (void *)token->prev);
        printf("  Token current: %p\n", (void *)token);
        printf("  Token next: %p\n", (void *)token->next);
        token = token->next;
    }
}

void print_redirs(t_redirs_list *redirs_list)
{   
    
    while (redirs_list)
    {   
        
        printf("Redirection type: %d\n", redirs_list->redir_type);
        printf("File: %s\n", redirs_list->file ? redirs_list->file : "(NULL)");
        printf("Delimiter: %s\n", redirs_list->delimiter ? redirs_list->delimiter : "(NULL)");
        redirs_list = redirs_list->next;
    }
}

void set_in_and_out(t_command_table *cmd_table)
{
    t_command_table *current_cmd = cmd_table;
    while (current_cmd)
    {
        t_redirs_list *redirs = current_cmd->redirs;
        while (redirs)
        {
            if (redirs->redir_type == R_IN)
            {
                current_cmd->simplecommand->input_fd = open(redirs->file, O_RDONLY);
                if (current_cmd->simplecommand->input_fd < 0)
                {
                    perror("Error opening input file");
                    return;
                }
            }
            else if (redirs->redir_type == R_OUT || redirs->redir_type == R_APP)
            {
                int flags = O_WRONLY | O_CREAT | ((redirs->redir_type == R_APP) ? O_APPEND : O_TRUNC);
                current_cmd->simplecommand->output_fd = open(redirs->file, flags, 0644);
                if (current_cmd->simplecommand->output_fd < 0)
                {
                    perror("Error opening output file");
                    return;
                }
            }
            redirs = redirs->next;
        }
        current_cmd = current_cmd->next;
    }
}

// int	parser(void)
// {
//     char                *new_line;
//     char                **split_line;
//     int                 token_count;
//     t_command_table     *command_table = NULL;
//     t_command_table     *current_table = NULL;
//     t_redirs_list       *redirs_list = NULL;

//     token_count = 0;
//     if (check_syntax_general(msh()->line)) 
//     {
//         new_line = add_spaces(msh()->line);
//         if (!new_line)
//             return (0);
//         split_line = split_by_spaces(new_line);
//         if (!split_line)
//             return (0);
//         while (split_line[token_count])
//         {
//             parse_redirections(split_line + token_count, &redirs_list);
//             t_command_table *new_table = init_cmd_table(0, NULL, NULL);
//             if (!new_table)
//             {
//                 ft_put_str_fd("Error: Failed to initialize command table.\n", STDERR_FILENO);
//                 free_redirs_list(redirs_list);
//                 return (0);
//             }
//             new_table->redirs = redirs_list;
//             redirs_list = NULL;
//             t_simple_command *simple_command = init_simple_command();
//             if (!simple_command)
//             {
//                 ft_put_str_fd("Error: Failed to initialize simple command.\n", STDERR_FILENO);
//                 free_redirs_list(new_table->redirs);
//                 free(new_table);
//                 return (0);
//             }
//             int start_token = token_count;
//             int arg_count = 0;
//             while (split_line[token_count] && strcmp(split_line[token_count], "|") != 0)
//             {
//                 if (strcmp(split_line[token_count], "<") == 0 ||
//                     strcmp(split_line[token_count], ">") == 0 ||
//                     strcmp(split_line[token_count], "<<") == 0 ||
//                     strcmp(split_line[token_count], ">>") == 0)
//                 {
//                     token_count += 2;
//                 }
//                 else
//                 {
//                     arg_count++;
//                     token_count++;
//                 }
//             }
//             simple_command->array_args = malloc((arg_count + 1) * sizeof(char *));
//             if (!simple_command->array_args)
//             {
//                 ft_put_str_fd("Error: Memory allocation failed for arguments.\n", STDERR_FILENO);
//                 free_redirs_list(new_table->redirs);
//                 free(new_table);
//                 free(simple_command);
//                 return (0);
//             }
//             int arg_index = 0;
//             for (int i = start_token; i < token_count; i++)
//             {
//                 if (strcmp(split_line[i], "<") == 0 ||
//                     strcmp(split_line[i], ">") == 0 ||
//                     strcmp(split_line[i], "<<") == 0 ||
//                     strcmp(split_line[i], ">>") == 0)
//                 {
//                     i++;
//                 }
//                 else
//                     simple_command->array_args[arg_index++] = ft_strdup(split_line[i]);
//             }
//             simple_command->array_args[arg_index] = NULL; // Null-terminate the array
//             simple_command->n_of_arg = arg_count;
//             simple_command->name = ft_strdup(simple_command->array_args[0]); // First argument is the command name
//             new_table->simplecommand = simple_command;
//             if (!command_table)
//                 command_table = new_table;
//             else
//                 current_table->next = new_table;
//             current_table = new_table;
//             if (split_line[token_count] && strcmp(split_line[token_count], "|") == 0)
//                 token_count++;
//         }
//         t_command_table *tmp = command_table;
//         msh()->cmd_table = command_table;
//         set_in_and_out(msh()->cmd_table);
//     }
//     return (1);
// }

int ft_compare(char **a, int n)
{
    if (ft_strcmp(a[n], "<") == 0 ||
                    ft_strcmp(a[n], ">") == 0 ||
                    ft_strcmp(a[n], "<<") == 0 ||
                    ft_strcmp(a[n], ">>") == 0)
        return (1);
    return(0);
}

int	parser(void)
{
    char                *new_line;
    char                **split_line;
    int                 token_count;
    t_simple_command    *simple_command;
    t_command_table     *command_table;
    t_command_table     *current_table;
    t_redirs_list       *redirs_list;
    int start_token;
    int arg_count;
    
    command_table = NULL;
    current_table = NULL;
    redirs_list = NULL;
    arg_count = 0;
    token_count = 0;
    if (check_syntax_general(msh()->line)) 
    {
        new_line = add_spaces(msh()->line);
        if (!new_line)
            return (0);
        split_line = split_by_spaces(new_line);
        if (!split_line)
            return (0);
        while (split_line[token_count])
        {
            parse_redirections(split_line + token_count, &redirs_list);
            t_command_table *new_table = init_cmd_table(0, NULL, NULL);
            if (!new_table)
            {
                ft_put_str_fd("Error: Failed to initialize command table.\n", STDERR_FILENO);
                free_redirs_list(redirs_list);
                return (0);
            }
            new_table->redirs = redirs_list;
            redirs_list = NULL;
            simple_command = init_simple_command();
            if (!simple_command)
            {
                ft_put_str_fd("Error: Failed to initialize simple command.\n", STDERR_FILENO);
                free_redirs_list(new_table->redirs);
                free(new_table);
                return (0);
            }
            start_token = token_count;
            while (split_line[token_count] && ft_strcmp(split_line[token_count], "|") != 0)
            {
                if (ft_compare(split_line, token_count))
                    token_count += 2;
                else
                {
                    arg_count++;
                    token_count++;
                }
            }
            simple_command->array_args = malloc((arg_count + 1) * sizeof(char *));
            if (!simple_command->array_args)
            {
                ft_put_str_fd("Error: Memory allocation failed for arguments.\n", STDERR_FILENO);
                free_redirs_list(new_table->redirs);
                free(new_table);
                free(simple_command);
                return (0);
            }
            int arg_index = 0;
            int i = start_token;
            while (i < token_count)
            {
                if (ft_compare(split_line, i))
                    i++;
                else
                    simple_command->array_args[arg_index++] = ft_strdup(split_line[i]);
                i++;
            }
            simple_command->array_args[arg_index] = NULL; // Null-terminate the array
            simple_command->n_of_arg = arg_count;
            simple_command->name = ft_strdup(simple_command->array_args[0]); // First argument is the command name
            new_table->simplecommand = simple_command;
            if (!command_table)
                command_table = new_table;
            else
                current_table->next = new_table;
            current_table = new_table;
            if (split_line[token_count] && ft_strcmp(split_line[token_count], "|") == 0)
                token_count++;
        }
        t_command_table *tmp = command_table;
        msh()->cmd_table = command_table;
        set_in_and_out(msh()->cmd_table);
    }
    return (1);
}
