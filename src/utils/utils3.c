/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:14:07 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 14:14:08 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_substr2(const char *str, int start, int len)
{
	char	*sub;

	sub = (char *)malloc(len + 1);
	if (!sub)
		return (NULL);
	ft_strncpy2(sub, str + start, len);
	sub[len] = '\0';
	return (sub);
}

int	count_words2(const char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (!str[i])
			break ;
		count++;
		while (str[i] && !ft_isspace(str[i]))
		{
			if (str[i] == '\'')
				skip_single_quote(str, &i);
			else if (str[i] == '"')
				skip_double_quote(str, &i);
			else
				i++;
		}
	}
	return (count);
}

int	find_substring_index(const char *haystack, const char *needle)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!haystack || !needle || !*needle)
		return (-1);
	while (haystack[i])
	{
		while (needle[j] && haystack[i + j] == needle[j])
			j++;
		if (!needle[j])
			return (i);
		i++;
	}
	return (-1);
}

int	parser_syntax_and_expand(void)
{
	int		heredoc_pos;
	int		check_len;
	char	*check_part;

	heredoc_pos = find_substring_index(msh()->line, "<<");
	if (heredoc_pos == -1)
		check_len = ft_strlen(msh()->line);
	else
		check_len = heredoc_pos;
	check_part = her_delim_check(msh()->line, check_len);
	if (check_unclosed_quotes(check_part))
	{
		msh()->exit_status = 2;
		free(check_part);
		return (0);
	}
	free(check_part);
	if (!check_syntax_general(msh()->tokens))
	{
		exit(msh()->exit_status = 2);
		return (0);
	}
	check_expansions();
	remove_quotes_from_tokens();
	return (1);
}

char	*her_delim_check(char *line, int check_len)
{
	int	tmp;

	tmp = check_len;
	while (line[check_len] != '\0')
	{
		if (line[check_len] == '\'' || line[check_len] == '"')
		{
			if ((line[check_len] == '\'' || line[check_len] == '"')
				&& line[check_len + 1] != '"' && line[check_len] != '\'')
				return (ft_substr(msh()->line, 0, ft_strlen(msh()->line)));
			if (line[check_len + 1] == '"')
				return (ft_substr(msh()->line, 0, check_len + 2));
			return (ft_substr(msh()->line, 0, check_len + 1));
		}
		check_len++;
	}
	return (ft_substr(msh()->line, 0, tmp + 3));
}
