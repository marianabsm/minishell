/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrito- <mabrito-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:20:32 by marianamest       #+#    #+#             */
/*   Updated: 2025/04/03 17:15:20 by mabrito-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    add_redir(t_redirs_list **head, t_redirs_list *new_node)
{
	t_redirs_list *tmp = *head;
	if (!tmp)
	{
		*head = new_node;
		return;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

void    add_cmd_info(t_simple_command **cmd, t_token *token)
{
    char    **cmd_arr;
    int     i;

    (*cmd)->n_of_arg++;
    cmd_arr = malloc(sizeof(char *) * ((*cmd)->n_of_arg + 1));
    i = -1;
    while (++i < (*cmd)->n_of_arg - 1)
        cmd_arr[i] = ft_strdup((*cmd)->array_args[i]);
    cmd_arr[i] = ft_strdup(token->content);
	cmd_arr[++i] = NULL;
    free_matrix((*cmd)->array_args);
    (*cmd)->array_args = cmd_arr;
}

void free_redirs_list(t_redirs_list *head)
{
	t_redirs_list *tmp;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->file);
		free(tmp->delimiter);
		free(tmp);
	}
}
