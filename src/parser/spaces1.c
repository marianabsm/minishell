/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:12:57 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 14:12:57 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	skip_single_quoted(const char *input, int *i, size_t *size)
{
	(*i)++;
	while (input[*i] && input[*i] != '\'')
	{
		(*size)++;
		(*i)++;
	}
	if (input[*i] == '\'')
		(*i)++;
}

static void	skip_double_quoted(const char *input, int *i, size_t *size)
{
	(*i)++;
	while (input[*i] && input[*i] != '"')
	{
		(*size)++;
		(*i)++;
	}
	if (input[*i] == '"')
		(*i)++;
}

static void	handle_special(const char *input, int *i, size_t *size)
{
	if ((input[*i] == '<' && input[*i + 1] == '<') || (input[*i] == '>'
			&& input[*i + 1] == '>'))
		*size += handle_double_special(input, i);
	else
		*size += handle_single_special(input, *i);
	(*i)++;
}

size_t	calculate_size(const char *input)
{
	size_t	size;
	int		i;

	i = 0;
	size = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'')
			skip_single_quoted(input, &i, &size);
		else if (input[i] == '"')
			skip_double_quoted(input, &i, &size);
		else if (is_special_char(input[i]))
			handle_special(input, &i, &size);
		else
		{
			size++;
			i++;
		}
	}
	return (size + 1);
}
