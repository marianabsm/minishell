/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitpid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:22:09 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 21:16:26 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	expand_var_and_write(int pipe_doc[2], char *str)
{
	char	*expanded;

	expanded = expand_var(ft_strdup(str));
	write_to_pipe(expanded, pipe_doc[1]);
	free(expanded);
}

static void	custom_sig(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

static void	freer(char *str, char *clean_delim)
{
	free(clean_delim);
	free(str);
}

void	read_into_heredoc(t_redirs_list *redir, int pipe_doc[2])
{
	char	*str;
	char	*clean_delim;

	clean_delim = remove_all_quotes(redir->delimiter);
	signals_ignore();
	safe_close(pipe_doc[0]);
	while (1)
	{
		custom_sig();
		str = readline("> ");
		if (!str)
			break ;
		if (ft_strcmp(str, clean_delim) == 0)
		{
			freer(str, clean_delim);
			break ;
		}
		if (str[0] == '$' && ft_strchr(redir->delimiter, '"') == 0)
			expand_var_and_write(pipe_doc, str);
		else
			write_to_pipe(str, pipe_doc[1]);
		free(str);
	}
	safe_close(pipe_doc[1]);
	exit(0);
}
