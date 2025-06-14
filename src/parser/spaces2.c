/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:24:06 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 14:12:53 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	double_quoted_string(const char *input, char *output, int *i, int *j)
{
	output[(*j)++] = input[(*i)++];
	while (input[*i] != '\0' && input[*i] != '"')
		output[(*j)++] = input[(*i)++];
	if (input[*i] == '"')
		output[(*j)++] = input[(*i)++];
}

void	single_quoted_string(const char *input, char *output, int *i, int *j)
{
	output[(*j)++] = input[(*i)++];
	while (input[*i] != '\0' && input[*i] != '\'')
		output[(*j)++] = input[(*i)++];
	if (input[*i] == '\'')
		output[(*j)++] = input[(*i)++];
}

int	check_open_single_quotes(const char *str)
{
	int	i;
	int	single_quote_open;

	single_quote_open = 0;
	i = 0;
	if (!str)
		return (0);
	while (str && str[i] != '\0')
	{
		if (str[i] == '\'')
			single_quote_open = !single_quote_open;
		i++;
	}
	return (single_quote_open == 0);
}

int	check_open_double_quotes(const char *str)
{
	int	i;
	int	double_quote_open;

	double_quote_open = 0;
	i = 0;
	if (!str)
		return (0);
	while (str && str[i] != '\0')
	{
		if (str[i] == '"')
			double_quote_open = !double_quote_open;
		i++;
	}
	return (double_quote_open == 0);
}

char	*add_spaces(char *in)
{
	int	i;
	int	j;
	int	in_single;
	int	in_double;

	i = 0;
	j = 0;
	in_single = 0;
	in_double = 0;
	msh()->output = (char *)malloc((calculate_size(in) * 2 + 1) * sizeof(char));
	if (msh()->output == NULL)
		return (NULL);
	while (in[i] != '\0')
	{
		if (in[i] == '"' && !in_single)
			double_quoted_string(in, msh()->output, &i, &j);
		else if (in[i] == '\'' && !in_double)
			single_quoted_string(in, msh()->output, &i, &j);
		else if (is_special_char(in[i]) && !in_single && !in_double)
			handle_special_char(in, msh()->output, &i, &j);
		else
			msh()->output[j++] = in[i++];
	}
	msh()->output[j] = '\0';
	return (msh()->output);
}
