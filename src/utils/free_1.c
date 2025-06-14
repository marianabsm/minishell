/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:17:41 by msilva-c          #+#    #+#             */
/*   Updated: 2025/06/10 19:30:47 by gcapa-pe         ###   ########.fr       */
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
	if (matrix)
		free(matrix);
}

void	free_simplecommand_and_table(t_command_table *cmd_table)
{
	if (cmd_table->simplecommand->array_args)
		free_matrix(cmd_table->simplecommand->array_args);
	if (cmd_table->simplecommand->path)
		free(cmd_table->simplecommand->path);
	if (cmd_table->simplecommand->name)
		free(cmd_table->simplecommand->name);
	if (cmd_table->simplecommand)
		free(cmd_table->simplecommand);
	if (cmd_table)
		free(cmd_table);
}

void	free_command_table(t_command_table *cmd_table)
{
	t_redirs_list	*tmp_redir;
	t_command_table	*temp;

	if (!cmd_table)
		return ;
	while (cmd_table)
	{
		temp = cmd_table->next;
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
		if (cmd_table->simplecommand->output_fd > 2)
			close(cmd_table->simplecommand->output_fd);
		if (fcntl(3, F_GETFD) != -1)
			close(3);
		free_simplecommand_and_table(cmd_table);
		cmd_table = temp;
	}
}
