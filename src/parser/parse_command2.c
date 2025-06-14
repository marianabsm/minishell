/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:13:38 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 14:13:39 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_redirs_list(t_redirs_list *head)
{
	t_redirs_list	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->file);
		free(tmp->delimiter);
		free(tmp);
	}
}

void	free_command_structs(t_simple_command *cmds, int n_commands)
{
	int	cmd_idx;
	int	arg_idx;

	if (!cmds)
		return ;
	cmd_idx = 0;
	while (cmd_idx < n_commands)
	{
		arg_idx = 0;
		while (arg_idx < cmds[cmd_idx].n_of_arg)
		{
			free(cmds[cmd_idx].array_args[arg_idx]);
			arg_idx++;
		}
		free(cmds[cmd_idx].array_args);
		cmd_idx++;
	}
	free(cmds);
}

void	add_redir(t_redirs_list **head, t_redirs_list *new_node)
{
	t_redirs_list	*tmp;

	tmp = *head;
	if (!tmp)
	{
		*head = new_node;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}
