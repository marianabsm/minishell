/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:13:34 by marianamest       #+#    #+#             */
/*   Updated: 2025/04/02 21:51:02 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void assign(const char *content, t_token *new_token, t_redirs_list *red_list)
{
    printf("next token: %s\n", new_token->next->content);
    if (ft_strcmp(content, "|") == 0)
        new_token->type = PIPE;
    else if (ft_strcmp(content, ">") == 0)
        new_token->type = R_OUT;
    else if (ft_strcmp(content, ">>") == 0)
        new_token->type = R_APP;
    else if (ft_strcmp(content, "<") == 0)
        new_token->type = R_IN;
    else if (ft_strcmp(content, "<<") == 0)
        new_token->type = HERE_DOC;
    else
        new_token->type = CMD;
    // if(new_token->type != CMD)
    //     set_redir(new_token->content, red_list, new_token->type, new_token);
}

t_token *create_token(const char *content, int index, t_redirs_list *red_list)
{
    t_token *new_token;

    new_token = (t_token *)malloc(sizeof(t_token));
    if (!new_token)
        return (NULL);
    new_token->content = ft_strdup(content);
    if (!new_token->content)
    {
        free(new_token);
        return (NULL);
    }
    assign(content, new_token,red_list);
    new_token->index = index;
    new_token->next = NULL;
    new_token->prev = NULL;
    return (new_token);
}

void add_token_to_list(t_token **head, t_token *new_token)
{
    t_token *temp;

    if (!*head)
    {
        *head = new_token;
        return;
    }
    temp = *head;
    while (temp->next)
        temp = temp->next;
    temp->next = new_token;
    new_token->prev = temp;
}

t_token *matrix_to_tokens(char **matrix, t_redirs_list *red_list)
{
    t_token *tokens;
    t_token *new_token;
    int i;

    tokens = NULL;
    i = 0;
    while (matrix[i])
    {
        printf("Creating token ->%s\n", matrix[i]);
        new_token = create_token(matrix[i], i, red_list);
        if (!new_token)
        {
            while (tokens)
            {
                t_token *temp = tokens;
                tokens = tokens->next;
                free(temp->content);
                free(temp);
            }
            return (NULL);
        }
        add_token_to_list(&tokens, new_token);
        i++;
    }
    return (tokens);
}
