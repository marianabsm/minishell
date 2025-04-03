/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 06:32:58 by msilva-c          #+#    #+#             */
/*   Updated: 2025/04/03 16:06:27 by marianamest      ###   ########.fr       */
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
//     t_command_table *command_table;
//     t_token *teste;

//     token_count = 0;
//     command_table = init_cmd_table(); // changed and now nana is lost
//     if (check_syntax_general(msh()->line))
//     {
//         //printf("%s\n", msh()->line);
//         new_line = add_spaces(msh()->line);
//         if(!new_line)
//             return(0);
//         //printf("%s\n", new_line);
//         split_line = split_by_spaces(new_line);
//         teste = matrix_to_tokens(split_line/*, command_table->redirs*/);
//         while (split_line[token_count])
//             token_count++; 
//         command_table->simplecommand = split_commands_into_structs(split_line, token_count, &n_commands);
//         if (!command_table->simplecommand)
//         {
//             ft_put_str_fd("Error: Failed to split commands into structs.\n", STDERR_FILENO);
//             return (0);
//         }
//         for (int i = 0; i < n_commands; i++)
//         {

//             printf("Command %d:\n", i + 1);
//             for (int j = 0; j < command_table->simplecommand[i].n_of_arg; j++)
//                 printf("  Arg %d: %s\n", j + 1, command_table->simplecommand[i].array_args[j]);
//         }
//         free_command_structs(command_table->simplecommand, n_commands);
//     }
//     return (1);
// }

int	parser(void)
{
    char                *new_line;
    char                **split_line;
    int                 n_commands;
    int                 token_count;
    t_redirs_list       *redirs_list = NULL;
    t_command_table     *command_table;
    t_token             *teste;

    token_count = 0;

    // Check syntax and prepare the input line
    if (check_syntax_general(msh()->line))
    {
        new_line = add_spaces(msh()->line);
        if (!new_line)
            return (0);

        split_line = split_by_spaces(new_line);
        if (!split_line)
            return (0);

        // Parse redirections from the tokens
        parse_redirections(split_line, &redirs_list);

        // Initialize the command table with the first redirection (if any)
        int redir_type = redirs_list ? redirs_list->redir_type : 0;
        char *redir_file = redirs_list ? redirs_list->file : NULL;
        char *redir_delimiter = redirs_list ? redirs_list->delimiter : NULL;

        command_table = init_cmd_table(redir_type, redir_file, redir_delimiter);
        if (!command_table)
        {
            ft_put_str_fd("Error: Failed to initialize command table.\n", STDERR_FILENO);
            free_redirs_list(redirs_list);
            return (0);
        }

        // Convert tokens to structures
        teste = matrix_to_tokens(split_line);
        while (split_line[token_count])
            token_count++;

        command_table->simplecommand = split_commands_into_structs(split_line, token_count, &n_commands);
        if (!command_table->simplecommand)
        {
            ft_put_str_fd("Error: Failed to split commands into structs.\n", STDERR_FILENO);
            free_redirs_list(redirs_list);
            free(command_table);
            return (0);
        }

        // Debugging: Print parsed commands
        for (int i = 0; i < n_commands; i++)
        {
            printf("Command %d:\n", i + 1);
            for (int j = 0; j < command_table->simplecommand[i].n_of_arg; j++)
                printf("  Arg %d: %s\n", j + 1, command_table->simplecommand[i].array_args[j]);
        }

        // Free resources
        free_command_structs(command_table->simplecommand, n_commands);
        free_redirs_list(redirs_list);
        free(command_table);
    }
    return (1);
}