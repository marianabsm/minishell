/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 06:32:58 by msilva-c          #+#    #+#             */
/*   Updated: 2025/03/22 16:51:32 by msilva-c         ###   ########.fr       */
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

int	parser(void)
{
	if (!check_quotes(msh()->line))
		return (0);
	if (!tokenizer())
        return (0);
    print_struct(&msh()->tokens);
	expander(msh()->tokens);
    printf("passed\n");
    if (!check_syntax(msh()->tokens))
        return (0);
    if (!set_exec())
        return (0);
    //até aqui tokens tá top
    rm_quotes_exec();
    print_exec(msh()->exec);
    return (1);
}
