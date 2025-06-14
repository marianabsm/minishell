/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:12:58 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 13:29:30 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	fill_matrix_with_tokens(char **matrix, char *input)
{
	int		i;
	int		k;
	char	*token;

	i = 0;
	k = 0;
	while (input[i])
	{
		token = extract_next_token(input, &i);
		if (ft_strcmp(token, "$EMPTY") == 0)
		{
			free(token);
			while (input[i] && ft_isspace(input[i]))
				i++;
			continue ;
		}
		matrix[k++] = token;
		while (input[i] && ft_isspace(input[i]))
			i++;
	}
	if (input[i] == '\0' && (i > 0 && ft_isspace(input[i - 1])))
		matrix[k++] = ft_strdup("");
	matrix[k] = NULL;
	return (k);
}

char	**split_by_spaces(char *input)
{
	int		input_len;
	char	**matrix;

	input_len = ft_strlen(input);
	matrix = malloc((input_len + 2) * sizeof(char *));
	if (!matrix)
		return (free(input), NULL);
	fill_matrix_with_tokens(matrix, input);
	free(input);
	return (matrix);
}
