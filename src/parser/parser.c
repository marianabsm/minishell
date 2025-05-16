/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 06:32:58 by msilva-c          #+#    #+#             */
/*   Updated: 2025/05/15 14:40:01 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//token list && exec

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
/////////////////////////// parser og madalena ////////////////////////

// int	parser(void)
// {
//     char    *new_line;
//     char    **split_line;
//     t_token *teste;

// 	//if (!check_quotes(msh()->line))
//     //{
//     //    //manda um error ?!TODO
// 	//	return (0);
//     //}
//     if(check_syntax_general(msh()->line))
//     {
//         printf("%s\n", msh()->line);
//         new_line = add_spaces(msh()->line);
//         printf("%s\n", new_line);
//         split_line = split_by_spaces(new_line);
//         teste = matrix_to_tokens(split_line); 
//     }
//     // while (teste->content)
//     // {
//     //     printf("%s\n", teste->content);
//     //     teste->content++;
//     // }
// 	//if (!tokenizer())
//      //   return (0);
//     //print_struct(&msh()->tokens);
// 	//expander(msh()->tokens);
//     //printf("passed\n");
//     //if (!check_syntax(msh()->tokens))
//     //    return (0);
//     //if (!set_exec())
//     //    return (0);
//     ////até aqui tokens tá top
//     //rm_quotes_exec();
//     //print_exec(msh()->exec);
//     return (1);
// }

// int	parser(void)
// {
//     char                *new_line;
//     char                **split_line;
//     int                 n_commands;
//     int                 token_count;
//     t_redirs_list       *redirs_list = NULL;
//     t_command_table     *command_table;
//     t_token             *teste;
//     int redir_type = 0;
//     char *redir_file = NULL;
//     char *redir_delimiter = NULL;
//     token_count = 0;
//     if (check_syntax_general(msh()->line))
//     {
//         new_line = add_spaces(msh()->line);
//         if (!new_line)
//             return (0);

//         split_line = split_by_spaces(new_line);
//         if (!split_line)
//             return (0);
//         parse_redirections(split_line, &redirs_list);
//         if (redirs_list)
//         {
//             redir_type = redirs_list->redir_type;
//             redir_file = redirs_list->file;
//             redir_delimiter = redirs_list->delimiter;
//         }
//         command_table = init_cmd_table(redir_type, redir_file, redir_delimiter);
//         if (!command_table)
//         {
//             ft_put_str_fd("Error: Failed to initialize command table.\n", STDERR_FILENO);
//             free_redirs_list(redirs_list);
//             return (0);
//         }
//         teste = matrix_to_tokens(split_line);
//         while (split_line[token_count])
//             token_count++;
//         command_table->simplecommand = split_commands_into_structs(split_line, token_count, &n_commands);
//         if (!command_table->simplecommand)
//         {
//             ft_put_str_fd("Error: Failed to split commands into structs.\n", STDERR_FILENO);
//             free_redirs_list(redirs_list);
//             free(command_table);
//             return (0);
//         }
//         // print_simple_command(command_table->simplecommand);
//         // print_simple_command(&command_table->simplecommand[1]);
//         // print_redirs(redirs_list);
//     }
//     free_command_structs(command_table->simplecommand, n_commands);
//     free_redirs_list(redirs_list);
//     free(command_table);
//     return (1);
// }

int	parser(void)
{
    char                *new_line;
    char                **split_line;
    int                 token_count;
    t_command_table     *command_table = NULL;
    t_command_table     *current_table = NULL;
    t_redirs_list       *redirs_list = NULL;

    token_count = 0;

    if (check_syntax_general(msh()->line))
    {
        new_line = add_spaces(msh()->line);
        if (!new_line)
            return (0);

        split_line = split_by_spaces(new_line);
        if (!split_line)
            return (0);

        // Parse tokens into commands and redirections
        while (split_line[token_count])
        {
            // Parse redirections for the current command
            parse_redirections(split_line + token_count, &redirs_list);

            // Create a new command table for the current command
            t_command_table *new_table = init_cmd_table(0, NULL, NULL);
            if (!new_table)
            {
                ft_put_str_fd("Error: Failed to initialize command table.\n", STDERR_FILENO);
                free_redirs_list(redirs_list);
                return (0);
            }

            // Assign redirections to the command table
            new_table->redirs = redirs_list;
            redirs_list = NULL; // Reset redirs_list for the next command

            // Parse the simple command arguments
            t_simple_command *simple_command = init_simple_command();
            if (!simple_command)
            {
                ft_put_str_fd("Error: Failed to initialize simple command.\n", STDERR_FILENO);
                free_redirs_list(new_table->redirs);
                free(new_table);
                return (0);
            }

            // Collect arguments, skipping redirection tokens
            int start_token = token_count;
            int arg_count = 0;
            while (split_line[token_count] && strcmp(split_line[token_count], "|") != 0)
            {
                if (strcmp(split_line[token_count], "<") == 0 ||
                    strcmp(split_line[token_count], ">") == 0 ||
                    strcmp(split_line[token_count], "<<") == 0 ||
                    strcmp(split_line[token_count], ">>") == 0)
                {
                    token_count += 2; // Skip redirection and its target
                }
                else
                {
                    arg_count++;
                    token_count++;
                }
            }

            // Allocate and copy arguments
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
            for (int i = start_token; i < token_count; i++)
            {
                if (strcmp(split_line[i], "<") == 0 ||
                    strcmp(split_line[i], ">") == 0 ||
                    strcmp(split_line[i], "<<") == 0 ||
                    strcmp(split_line[i], ">>") == 0)
                {
                    i++; // Skip redirection target
                }
                else
                {
                    simple_command->array_args[arg_index++] = ft_strdup(split_line[i]);
                }
            }
            simple_command->array_args[arg_index] = NULL; // Null-terminate the array
            simple_command->n_of_arg = arg_count;

            new_table->simplecommand = simple_command;

            // Add the new command table to the linked list
            if (!command_table)
                command_table = new_table;
            else
                current_table->next = new_table;
            current_table = new_table;

            // Skip the pipe token
            if (split_line[token_count] && strcmp(split_line[token_count], "|") == 0)
                token_count++;
        }

        // Print the command table
        // print_command_table(command_table);

        // Free the command table
        //free_command_table(command_table);
        t_command_table *tmp = command_table;
        int i = -1;
        while (tmp)
        {
            while (++i < tmp->simplecommand->n_of_arg)
            {
                printf("Before Expander -> %s\n", tmp->simplecommand->array_args[i]);
                tmp->simplecommand->array_args[i] = expand_var(tmp->simplecommand->array_args[i]);
                printf("After Expander -> %s\n", tmp->simplecommand->array_args[i]);
            }
            tmp = tmp->next;
        }
        
    }
    return (1);
}
