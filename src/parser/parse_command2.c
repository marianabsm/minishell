/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:20:32 by marianamest       #+#    #+#             */
/*   Updated: 2025/05/01 15:02:03 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	parse_redirections(char **tokens, t_redirs_list **redirs_list)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], ">") == 0)
		{
			add_redir(redirs_list, init_redirs_list(R_OUT, tokens[i + 1],
					NULL));
			i++;
		}
		else if (ft_strcmp(tokens[i], ">>") == 0)
		{
			add_redir(redirs_list, init_redirs_list(R_APP, tokens[i + 1],
					NULL));
			i++;
		}
		else if (ft_strcmp(tokens[i], "<") == 0)
		{
			add_redir(redirs_list, init_redirs_list(R_IN, tokens[i + 1], NULL));
			i++;
		}
		else if (ft_strcmp(tokens[i], "<<") == 0)
		{
			add_redir(redirs_list, init_redirs_list(HERE_DOC, NULL, tokens[i
					+ 1]));
			i++;
		}
		else if (ft_strcmp(tokens[i], "|") == 0)
		{
			add_redir(redirs_list, init_redirs_list(PIPE, NULL, NULL));
		}
		i++;
	}
}
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
