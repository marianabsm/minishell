/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:12:49 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 14:12:50 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_special_char(const char *input, char *output, int *i, int *j)
{
	if (*j > 0 && output[*j - 1] != ' ')
		output[(*j)++] = ' ';
	output[(*j)++] = input[(*i)++];
	if ((input[*i - 1] == '<' && input[*i] == '<') || (input[*i - 1] == '>'
			&& input[*i] == '>'))
		output[(*j)++] = input[(*i)++];
	if (input[*i] != ' ' && input[*i] != '\0')
		output[(*j)++] = ' ';
}

size_t	handle_double_special(const char *input, int *i)
{
	size_t	extra;

	extra = 0;
	(*i)++;
	if (*i == 1 || input[*i - 2] != ' ')
		extra++;
	if (input[*i + 1] != ' ')
		extra++;
	return (extra);
}

size_t	handle_single_special(const char *input, int i)
{
	size_t	extra;

	extra = 0;
	if (i == 0 || input[i - 1] != ' ')
		extra++;
	if (input[i + 1] != ' ')
		extra++;
	return (extra);
}
