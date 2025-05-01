/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 06:32:58 by msilva-c          #+#    #+#             */
/*   Updated: 2025/05/01 15:02:06 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// token list && exec

void	print_msh(t_msh *msh)
{
	t_token	*token;

	if (!msh)
	{
		printf("msh is NULL\n");
		return ;
	}
	printf("msh->line: %s\n", msh->line ? msh->line : "(NULL)");
	printf("msh->home: %s\n", msh->home ? msh->home : "(NULL)");
	printf("msh->pwd: %s\n", msh->pwd ? msh->pwd : "(NULL)");
	printf("msh->env: %p\n", (void *)msh->env);
	printf("msh->exec: %p\n", (void *)msh->exec);
	printf("msh->exit: %d\n", msh->exit_status);
	printf("Tokens:\n");
	token = msh->tokens;
	if (!token)
		printf("(NULL)\n");
	while (token)
	{
		printf("  Token content: %s\n",
			token->content ? token->content : "(NULL)");
		printf("  Token type: %d\n", token->type);
		printf("  Token index: %d\n", token->index);
		printf("  Token prev: %p\n", (void *)token->prev);
		printf("  Token current: %p\n", (void *)token);
		printf("  Token next: %p\n", (void *)token->next);
		token = token->next;
	}
}

int	parser(void)
{
	char				*new_line;
	char				**split_line;
	int					token_count;
	t_command_table		*command_table;
	t_command_table		*current_table;
	t_redirs_list		*redirs_list;
	t_command_table		*new_table;
	t_simple_command	*simple_command;
	int					start_token;
	int					arg_count;
	int					arg_index;
	t_command_table		*tmp;
	int					i;

	command_table = NULL;
	current_table = NULL;
	redirs_list = NULL;
	token_count = 0;
	if (check_syntax_general(msh()->line))
	{
		new_line = add_spaces(msh()->line);
		if (!new_line)
			return (0);
		split_line = split_by_spaces(new_line);
		if (!split_line)
			return (0);
		// Parse tokens into commands and redirections
		while (split_line[token_count])
		{
			// Parse redirections for the current command
			parse_redirections(split_line + token_count, &redirs_list);
			// Create a new command table for the current command
			new_table = init_cmd_table(0, NULL, NULL);
			if (!new_table)
			{
				ft_put_str_fd("Error: Failed to initialize command table.\n",
					STDERR_FILENO);
				free_redirs_list(redirs_list);
				return (0);
			}
			// Assign redirections to the command table
			new_table->redirs = redirs_list;
			redirs_list = NULL; // Reset redirs_list for the next command
			// Parse the simple command arguments
			simple_command = init_simple_command();
			if (!simple_command)
			{
				ft_put_str_fd("Error: Failed to initialize simple command.\n",
					STDERR_FILENO);
				free_redirs_list(new_table->redirs);
				free(new_table);
				return (0);
			}
			// Collect arguments, skipping redirection tokens
			start_token = token_count;
			arg_count = 0;
			while (split_line[token_count] && strcmp(split_line[token_count],
					"|") != 0)
			{
				if (strcmp(split_line[token_count], "<") == 0
					|| strcmp(split_line[token_count], ">") == 0
					|| strcmp(split_line[token_count], "<<") == 0
					|| strcmp(split_line[token_count], ">>") == 0)
				{
					token_count += 2; // Skip redirection and its target
				}
				else
				{
					arg_count++;
					token_count++;
				}
			}
			// Allocate and copy arguments
			simple_command->array_args = malloc((arg_count + 1)
					* sizeof(char *));
			if (!simple_command->array_args)
			{
				ft_put_str_fd("Error: Memory allocation failed for arguments.\n",
					STDERR_FILENO);
				free_redirs_list(new_table->redirs);
				free(new_table);
				free(simple_command);
				return (0);
			}
			arg_index = 0;
			for (int i = start_token; i < token_count; i++)
			{
				if (strcmp(split_line[i], "<") == 0 || strcmp(split_line[i],
						">") == 0 || strcmp(split_line[i], "<<") == 0
					|| strcmp(split_line[i], ">>") == 0)
				{
					i++; // Skip redirection target
				}
				else
				{
					simple_command->array_args[arg_index++] = ft_strdup(split_line[i]);
				}
			}
			simple_command->array_args[arg_index] = NULL;
				// Null-terminate the array
			simple_command->n_of_arg = arg_count;
			new_table->simplecommand = simple_command;
			// Add the new command table to the linked list
			if (!command_table)
				command_table = new_table;
			else
				current_table->next = new_table;
			current_table = new_table;
			// Skip the pipe token
			if (split_line[token_count] && strcmp(split_line[token_count],
					"|") == 0)
				token_count++;
		}
		// Print the command table
		print_command_table(command_table);
		// Free the command table
		// free_command_table(command_table);
		tmp = command_table;
		i = -1;
		while (tmp)
		{
			while (++i < tmp->simplecommand->n_of_arg)
			{
				printf("Before Expander -> %s\n",
					tmp->simplecommand->array_args[i]);
				tmp->simplecommand->array_args[i] = expand_var(tmp->simplecommand->array_args[i]);
				printf("After Expander -> %s\n",
					tmp->simplecommand->array_args[i]);
			}
			tmp = tmp->next;
		}
	}
	return (1);
}
