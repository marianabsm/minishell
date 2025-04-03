/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:20:32 by marianamest       #+#    #+#             */
/*   Updated: 2025/04/02 21:50:46 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void set_redir(char *arg, t_redirs_list *red_list, int type, t_token *token)
// {
//     t_redirs_list *first;

//     first = red_list;
//     while(red_list != NULL)
//         red_list = red_list->next;
//     red_list->redir_type = type;
//     red_list->file = token->next->content;
// }