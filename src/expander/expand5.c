/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:11:33 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 22:30:50 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	handle_single_quote(char **new_input, char *input,
		t_quote_state *qs)
{
	if (input[qs->i] == '\'' && !qs->in_double)
	{
		qs->in_single = !(qs->in_single);
		append_char(new_input, input[qs->i]);
		qs->i++;
		return (1);
	}
	return (0);
}

static int	handle_double_quote(char **new_input, char *input,
		t_quote_state *qs)
{
	if (input[qs->i] == '"' && !qs->in_single)
	{
		qs->in_double = !(qs->in_double);
		append_char(new_input, input[qs->i]);
		qs->i++;
		return (1);
	}
	return (0);
}

static int	handle_dollar_double_quote(char *input, t_quote_state *qs)
{
	int	j;

	if (input[qs->i] == '$' && input[qs->i + 1] == '"')
	{
		j = qs->i + 2;
		while (input[j] && input[j] != '"')
			j++;
		if (input[j] == '"')
			j++;
		qs->i = j;
		return (1);
	}
	return (0);
}

static int	handle_dollar_expansion(char **new_input, char *input,
		t_quote_state *qs)
{
	if (input[qs->i] == '$' && !qs->in_single && should_expand(&input[qs->i]))
	{
		if (!handle_dollar(new_input, input, &(qs->i)))
			return (-1);
		return (1);
	}
	return (0);
}

int	expand_var_loop(char **new_input, char *input, int i)
{
	t_quote_state	qs;
	int				dollar_result;

	qs.in_single = 0;
	qs.in_double = 0;
	qs.i = i;
	while (input[qs.i])
	{
		if (handle_single_quote(new_input, input, &qs))
			continue ;
		if (handle_double_quote(new_input, input, &qs))
			continue ;
		if (handle_dollar_double_quote(input, &qs))
			continue ;
		dollar_result = handle_dollar_expansion(new_input, input, &qs);
		if (dollar_result == -1)
			return (-1);
		if (dollar_result == 1)
			continue ;
		append_char(new_input, input[qs.i]);
		qs.i++;
	}
	free(input);
	return (0);
}
