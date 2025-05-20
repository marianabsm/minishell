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
	t_command_table	*temp;

	if (!cmd_table)
		return ;
	while (cmd_table)
	{
		temp = cmd_table->next;
		free(cmd_table);
		cmd_table = temp;
	}
}

void	free_exec(t_exec *ex)
{
	if (ex->args)
		free_matrix(ex->envp);
	if (ex->envp)
		free_matrix(ex->envp);
}
