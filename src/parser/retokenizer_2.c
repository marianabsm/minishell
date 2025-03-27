/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retokenizer_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 04:46:51 by msilva-c          #+#    #+#             */
/*   Updated: 2025/03/20 23:10:40 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	re_token(t_token *head)
{
	t_token	*temp;

	temp = head;
	while (temp)
	{
		// printf("  needs_retoken: %s\n", needs_retoken(temp->content));
		if (needs_retoken(temp->content))
		{
			//printf("going to get_which\n");
			temp = update_token(temp);
		}
		else
			temp = temp->next;
	}
}
