/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 01:38:25 by msilva-c          #+#    #+#             */
/*   Updated: 2025/06/10 18:02:18 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	help_close_and_free(t_command_table *cmd_table)
{
	close_cmd_table_fds(cmd_table);
	free_command_table(cmd_table);
	cmd_table = NULL;
}

static void	help_free_and_close_pipes(t_exec *exec)
{
	free(exec->pid);
	close_pipes(exec);
	free(exec);
}

static void	help_free(void)
{
	free_tokens(msh()->tokens);
	msh()->tokens = NULL;
}

void	free_and_exit(t_msh *m)
{
	if (!m)
		return ;
	if (m->original_stdout > 2)
		close(m->original_stdout);
	if (m->original_stdin > 2)
		close(m->original_stdin);
	if (m->cmd_table)
		help_close_and_free(m->cmd_table);
	if (m->tokens)
		help_free();
	clear_history();
	rl_clear_history();
	if (m->line)
		free(m->line);
	if (m->home)
		free(m->home);
	if (m->pwd)
		free(m->pwd);
	if (m->env)
		free_matrix(m->env);
	if (m->env_list)
		free_env(m->env_list);
	if (m->exec)
		help_free_and_close_pipes(m->exec);
}

void	free_token_list(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		if (tokens->content)
			free(tokens->content);
		free(tokens);
		tokens = tmp;
	}
}
