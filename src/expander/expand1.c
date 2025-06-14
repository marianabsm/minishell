/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:42:49 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/09 21:21:45 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_and_size_var_name(char *in)
{
	int	i;
	int	j;

	i = 0;
	if (!in)
		return (0);
	while (in[i])
	{
		if (in[i] == '$')
		{
			j = i;
			i++;
			if (in[i] == '"')
				i++;
			if (ft_isdigit(in[i]) || (!ft_isalnum(in[i]) && in[i] != '_'))
				return (0);
			while (in[i] && (in[i] == '_' || ft_isalnum(in[i])))
				i++;
			if (in[i] == '"')
				i++;
			return (i - j - 1);
		}
		i++;
	}
	return (0);
}

char	*find_var_name2(char *input, int size_of_var_name)
{
	int		i;
	int		j;
	char	*var_name;

	if (size_of_var_name <= 0)
		return (NULL);
	var_name = malloc(sizeof(char) * (size_of_var_name + 1));
	if (!var_name)
		return (NULL);
	i = 0;
	while (input[i] != '$')
		i++;
	i++;
	if (input[i] == '"')
		i++;
	j = 0;
	while (input[i] && (input[i] == '_' || ft_isalnum(input[i])))
	{
		var_name[j++] = input[i++];
	}
	var_name[j] = '\0';
	return (var_name);
}

char	*find_var_in_env(char *input, char *var_name, char **env)
{
	int		i;
	char	*var_value;
	char	*temp;

	i = 0;
	var_value = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, ft_strlen(var_name)) == 0
			&& env[i][ft_strlen(var_name)] == '=')
		{
			var_value = ft_strdup(env[i] + ft_strlen(var_name) + 1);
			return (var_value);
		}
		i++;
	}
	temp = delete_name_and_dollar_sign(input, var_name);
	free(temp);
	return (ft_strdup(""));
}

char	*delete_number_and_dollar_sign(char *input, int dollar_index)
{
	char	*new_input;
	int		j;

	new_input = (char *)malloc(sizeof(char) * (ft_strlen(input) - 2));
	if (!new_input)
		return (NULL);
	j = 0;
	while (input[j])
	{
		if (j == dollar_index || j == dollar_index + 1)
			j++;
		new_input[j] = input[j];
		j++;
	}
	new_input[j] = '\0';
	free(input);
	return (new_input);
}

char	*delete_dollar_sign(char *input, int dollar_index)
{
	char	*new_input;
	int		j;

	new_input = (char *)malloc(sizeof(char) * (ft_strlen(input) - 1));
	if (!new_input)
		return (NULL);
	j = 0;
	while (input[j])
	{
		if (j == dollar_index)
			j++;
		new_input[j] = input[j];
		j++;
	}
	new_input[j] = '\0';
	free(input);
	return (new_input);
}
