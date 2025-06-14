/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:11:45 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 16:32:55 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_quotes_from_tokens(void)
{
	t_token	*tok;
	char	*stripped;
	int		is_heredoc_delim;

	tok = msh()->tokens;
	is_heredoc_delim = 0;
	while (tok)
	{
		if (is_heredoc_delim)
		{
			stripped = ft_strdup(tok->content);
			is_heredoc_delim = 0;
		}
		else
			stripped = remove_all_quotes(tok->content);
		if (tok->content)
			free(tok->content);
		tok->content = stripped;
		if (ft_strcmp(tok->content, "<<") == 0 && tok->next
			&& ft_strchr(tok->content, '\'') == NULL)
			is_heredoc_delim = 1;
		tok = tok->next;
	}
}

static void	update_quote_state(char c, int *in_single, int *in_double)
{
	if (c == '\'' && !(*in_double))
		*in_single = !(*in_single);
	else if (c == '"' && !(*in_single))
		*in_double = !(*in_double);
}

static char	*copy_without_quotes(const char *str)
{
	int		i;
	int		j;
	int		in_single;
	int		in_double;
	char	*new_str;

	i = 0;
	j = 0;
	in_single = 0;
	in_double = 0;
	new_str = malloc(ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '\'' && !in_double) || (str[i] == '"' && !in_single))
			update_quote_state(str[i], &in_single, &in_double);
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*remove_all_quotes(char *str)
{
	if (!str)
		return (NULL);
	return (copy_without_quotes(str));
}

int	check_unclosed_quotes(char *str)
{
	int	i;
	int	in_single;
	int	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '"' && !in_single)
			in_double = !in_double;
		i++;
	}
	return (in_single || in_double);
}
