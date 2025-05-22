/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testers_for_printing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:54:04 by marianamest       #+#    #+#             */
/*   Updated: 2025/05/21 12:54:24 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


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

void print_msh(t_msh *msh)
{
    t_command_table *table;
    t_token *token;
    int     i;

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
    table = msh->cmd_table;
    while (table)
    {
        i = -1;
        while(++i < table->simplecommand->n_of_arg)
            printf("Cmd argument: %s\n", table->simplecommand->array_args[i]);
        print_redirs(table->redirs);
        printf("Next command\n");
        table = table->next;
    }
}