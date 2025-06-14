/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:12:43 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 14:12:44 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*extract_token_part(const char *input, int *i)
{
	if (input[*i] == '"')
		return (extract_double_quoted(input, i));
	else if (input[*i] == '\'')
		return (extract_single_quoted(input, i));
	else
		return (extract_unquoted(input, i));
}

static char	*join_token_parts(char *result, char *temp)
{
	char	*joined;

	joined = ft_strjoin(result, temp);
	free(result);
	free(temp);
	return (joined);
}

char	*extract_next_token(const char *input, int *i)
{
	char	*temp;
	char	*result;
	int		start;

	result = NULL;
	start = *i;
	if (input[*i] && ft_isspace(input[*i]))
	{
		(*i)++;
		return (ft_strdup(""));
	}
	while (input[*i] && !ft_isspace(input[*i]))
	{
		temp = extract_token_part(input, i);
		if (!result)
			result = temp;
		else
			result = join_token_parts(result, temp);
	}
	if (!result && start == *i)
		return (ft_strdup(""));
	return (result);
}
