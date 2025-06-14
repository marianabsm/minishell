/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:42:49 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/09 00:19:33 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*should_not_expand(char *input)
{
	char	*temp;

	if (input[0] == '"' && input[ft_strlen(input) - 1] == '"')
	{
		temp = ft_strtrim(input, '"');
		free(input);
		if (!temp)
			return (ft_strdup(""));
		return (temp);
	}
	if (input[0] == '\'' && input[ft_strlen(input) - 1] == '\'')
	{
		temp = ft_strtrim(input, '\'');
		free(input);
		if (!temp)
			return (ft_strdup(""));
		return (temp);
	}
	return (input);
}
