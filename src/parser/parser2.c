/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:25:31 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 01:52:26 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_parser(void)
{
	if (!parser())
	{
		prep_next_cmdline(msh());
		return (0);
	}
	return (1);
}

int	ft_compare(char **split_line, int i)
{
	if (ft_strcmp(split_line[i], "<") == 0 || ft_strcmp(split_line[i], ">") == 0
		|| ft_strcmp(split_line[i], ">>") == 0 || ft_strcmp(split_line[i],
			"<<") == 0)
		return (1);
	return (0);
}

void	check_expansions(void)
{
	t_token	*tok;
	char	*expanded;
	int		first_token;

	first_token = 1;
	tok = msh()->tokens;
	while (tok)
	{
		if (tok->content[0] == '\'' && tok->content[ft_strlen(tok->content)
				- 1] == '\'')
			first_token = 0;
		if (!first_token && should_expand(tok->content))
		{
			expanded = expand_var(ft_strdup(tok->content));
			free(tok->content);
			tok->content = expanded;
		}
		first_token = 0;
		tok = tok->next;
	}
}

t_simple_command	*initialize_simple_command(void)
{
	t_simple_command	*new_table;

	if (msh()->tokens && msh()->tokens->content[0] == '\0')
	{
		msh()->tokens = msh()->tokens->next;
	}
	new_table = init_simple_command();
	if (!new_table)
		return (NULL);
	return (new_table);
}

int	parser_process_command(t_command_table **command_table)
{
	if (!process_command(command_table))
	{
		if (*command_table)
			free_command_table(*command_table);
		return (0);
	}
	return (1);
}
