/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:36:43 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 01:30:02 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	should_expand(char *input)
{
	int	in_single;
	int	in_double;
	int	i;

	in_single = 0;
	in_double = 0;
	i = 0;
	if (!input)
		return (0);
	while (input[i])
	{
		if (input[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (input[i] == '"' && !in_single)
			in_double = !in_double;
		else if (input[i] == '$' && !in_single)
			return (1);
		i++;
	}
	return (0);
}

char	*delete_name_and_dollar_sign(char *input, char *var_name)
{
	char	*new_input;
	int		i;
	int		j;

	j = 0;
	i = 0;
	new_input = (char *)malloc(sizeof(char) * (ft_strlen(input)
				- ft_strlen(var_name) - 1));
	if (!new_input)
		return (NULL);
	while (input[i] && input[i] != '$')
		new_input[j++] = input[i++];
	i += ft_strlen(var_name) + 1;
	while (input[i] && input[j])
		new_input[j++] = input[i++];
	return (new_input);
}

char	*ft_strjoin_char(char *s1, char c)
{
	char	*result;
	int		len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	result = malloc(sizeof(char) * (len + 2));
	if (!result)
		return (NULL);
	ft_strcpy(result, s1);
	result[len] = c;
	result[len + 1] = '\0';
	return (result);
}

char	*weird_cases(char *input)
{
	if (input[0] == '\'' && input[ft_strlen(input) - 1] == '\'')
		return (ft_strtrim(input, 39));
	if (input[0] == '$' && input[1] == '\'')
	{
		if (input[ft_strlen(input) - 1] == '\'')
			return (ft_strtrim(ft_strtrim(input, '$'), 39));
	}
	if (input[0] == '$' && input[1] == '"')
	{
		if (input[ft_strlen(input) - 1] == '"')
			return (ft_strtrim(ft_strtrim(input, '$'), '"'));
	}
	return (ft_strdup(input));
}

char	*expand_exit_status(char *input, int dollar_index)
{
	char	*exit_status_str;
	char	*new_input;
	int		new_len;

	exit_status_str = ft_itoa(msh()->exit_status);
	if (!exit_status_str)
		return (NULL);
	new_len = ft_strlen(input) - 2 + ft_strlen(exit_status_str);
	new_input = (char *)malloc(sizeof(char) * (new_len + 1));
	if (!new_input)
	{
		free(exit_status_str);
		return (NULL);
	}
	ft_strlcpy(new_input, input, dollar_index + 1);
	ft_strlcat(new_input, exit_status_str, new_len + 1);
	ft_strlcat(new_input, input + dollar_index + 2, new_len + 1);
	free(exit_status_str);
	free(input);
	return (new_input);
}
