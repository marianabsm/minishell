/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:12:45 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 14:12:46 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*extract_double_quoted(const char *input, int *i)
{
	int		start;
	char	*temp;

	start = *i;
	(*i)++;
	while (input[*i] && input[*i] != '"')
		(*i)++;
	if (input[*i] == '"')
		(*i)++;
	temp = ft_substr2(input, start, *i - start);
	return (temp);
}

char	*extract_single_quoted(const char *input, int *i)
{
	int		start;
	char	*temp;

	start = *i;
	(*i)++;
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	if (input[*i] == '\'')
		(*i)++;
	temp = ft_substr2(input, start, *i - start);
	return (temp);
}

char	*extract_unquoted(const char *input, int *i)
{
	int		start;
	char	*temp;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '"'
		&& input[*i] != '\'')
		(*i)++;
	temp = ft_substr2(input, start, *i - start);
	return (temp);
}

void	skip_single_quote(const char *str, int *i)
{
	(*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (str[*i] == '\'')
		(*i)++;
}

void	skip_double_quote(const char *str, int *i)
{
	(*i)++;
	while (str[*i] && str[*i] != '"')
		(*i)++;
	if (str[*i] == '"')
		(*i)++;
}
