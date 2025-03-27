/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 22:49:40 by msilva-c          #+#    #+#             */
/*   Updated: 2025/03/19 15:35:05 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// rever
int	count_words(char *line)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]) || (in_quotes(line, i) && ft_isspace(line[i])))
		{
			word++;
			while ((!ft_isspace(line[i]) || (in_quotes(line, i)
						&& ft_isspace(line[i]))) && line[i])
				i++;
		}
		if (ft_isspace(line[i]) && !in_quotes(line, i))
			i++;
	}
	return (word);
}

int	parser_wdlen(char *line, int i)
{
	int	len;

	len = 0;
	while (line[i + len])
	{
		if (!ft_isspace(line[i + len]))
			len++;
		else if (ft_isspace(line[i + len]) && in_quotes(line, i + len))
			// test: see if in_quotes is working
			len++;
		else
			return (len);
	}
	return (len);
}

char	**split_spaces(char *line)
{
	char	**matrix;
	int		wc;
	int		i;
	int		j;

	i = 0;
	j = 0;
	wc = count_words(line);
	matrix = (char **)safe_malloc(sizeof(char *) * (wc + 1));
	if (!matrix)
		return (NULL);
	while (j < wc)
	{
		while (ft_isspace(line[i]))
			i++;
		matrix[j] = ft_substr(line, i, parser_wdlen(line, i));
		// ver se está a guardar bem
		if (!matrix[j++])
			return (matrix);
		i += parser_wdlen(line, i);
	}
	matrix[j] = NULL;
	return (matrix);
}
