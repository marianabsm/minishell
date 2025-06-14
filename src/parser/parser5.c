/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:13:28 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 14:13:29 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_table_add_back(t_command_table **table, t_command_table *new_node)
{
	t_command_table	*tmp;

	tmp = *table;
	if (!tmp)
	{
		*table = new_node;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

void	help_parser(t_command_table *command_table)
{
	free_tokens(msh()->tokens);
	msh()->tokens = NULL;
	msh()->cmd_table = command_table;
	if (set_in_and_out(msh()->cmd_table) == 1)
	{
		reset_fds();
		free_command_table(msh()->cmd_table);
		msh()->cmd_table = NULL;
	}
}

char	*parser_add_spaces(void)
{
	return (add_spaces(msh()->line));
}

char	**parser_split_line(char *new_line)
{
	if (ft_strcmp(new_line, "$PWD") == 0)
	{
		free(new_line);
		msh()->exit_status = 126;
		printf("minishell: %s: Is a directory\n", get_home());
		return (NULL);
	}
	return (split_by_spaces(new_line));
}

int	parser_tokens(char **split_line)
{
	t_token	*tmp;

	tmp = matrix_to_tokens(split_line);
	if (!tmp)
	{
		free_token_list(tmp);
		return (0);
	}
	if (tmp && tmp->next == NULL && tmp->type == CMD && tmp->content[0] == '$')
	{
		free_token_list(tmp);
		return (0);
	}
	msh()->tokens = tmp;
	return (1);
}
