/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:17:41 by msilva-c          #+#    #+#             */
/*   Updated: 2025/05/20 13:58:01 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*temp;

	if (!tokens)
		return ;
	current = tokens;
	temp = tokens;
	while (current)
	{

		temp = current->next;
		if (current)
		{
			if (current->content != NULL)
				free(current->content);
			free(current);
		}
		current = temp;
	}
}

void	free_var(t_env *var)
{
	if (!var)
		return ;
	if (var->var)
		free(var->var);
	if (var->var_name)
		free(var->var_name);
	if (var->var_value)
		free(var->var_value);
	free(var);
}

void	free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}


void free_command_table(t_command_table *cmd_table)
{
	t_redirs_list	*tmp_redir;
	t_command_table	*temp;

	if (!cmd_table)
		return ;
	while (cmd_table)
	{
		temp = cmd_table->next;
		if (cmd_table->simplecommand->input_fd > 0)
		{
			printf("Closed infile %d\n", cmd_table->simplecommand->input_fd);
			close(cmd_table->simplecommand->input_fd);
			cmd_table->simplecommand->input_fd = 0;
		}
		if (cmd_table->simplecommand->output_fd > 1)
		{
			printf("Closed outfile %d\n", cmd_table->simplecommand->output_fd);
			close(cmd_table->simplecommand->output_fd);
			cmd_table->simplecommand->output_fd = 1;
		}
		while (cmd_table->redirs)
		{
			tmp_redir = cmd_table->redirs->next;
			if (cmd_table->redirs->delimiter)
				free(cmd_table->redirs->delimiter);
			if (cmd_table->redirs->file)
				free(cmd_table->redirs->file);
			free(cmd_table->redirs);
			cmd_table->redirs = tmp_redir;
		}
		free_matrix(cmd_table->simplecommand->array_args);
		free(cmd_table->simplecommand);
		free(cmd_table);
		cmd_table = temp;
	}
}

