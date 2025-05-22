/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:14:22 by marianamest       #+#    #+#             */
/*   Updated: 2025/05/20 14:20:17 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_syntax_general(t_token *tokens)
{
    while (tokens)
    {
        if (tokens->type == PIPE && (!tokens->prev || !tokens->next || tokens->next->type == PIPE))
        {
            ft_putstr_fd(PIPE_SYNT_ERR, STDERR_FILENO);
            return (0);
        }
        if ((tokens->type == R_APP || tokens->type == R_IN
                || tokens->type == R_OUT || tokens->type == HERE_DOC)
                && (!tokens->next || tokens->next->type != CMD))
        {
            if (tokens->type == R_APP)
                ft_putstr_fd(APP_SYNT_ERR, STDERR_FILENO);
            if (tokens->type == R_IN)
                ft_putstr_fd(IN_SYNT_ERR, STDERR_FILENO);
            if (tokens->type == R_OUT)
                ft_putstr_fd(OUT_SYNT_ERR, STDERR_FILENO);
            if (tokens->type == HERE_DOC)
                ft_putstr_fd(HEREDOC_SYNT_ERR, STDERR_FILENO);
            return (0);
        }
        tokens = tokens->next;
    }
    return (1);
}

