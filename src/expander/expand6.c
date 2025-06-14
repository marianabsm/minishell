/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:11:36 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 22:30:36 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_var(char *input)
{
	char	*new_input;

	if (!input)
		return (NULL);
	new_input = ft_strdup("");
	if (!new_input)
	{
		free(input);
		return (NULL);
	}
	if (expand_var_loop(&new_input, input, 0) == -1)
		return (new_input);
	return (new_input);
}

void	remove_empty_args(char **args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!args)
		return ;
	while (args[i])
	{
		if (args[i][0] != '\0')
			args[j++] = args[i];
		else
			free(args[i]);
		i++;
	}
	args[j] = NULL;
}

int	handle_dollar(char **new_input, char *input, int *i)
{
	if (input[*i + 1] == '?')
		return (handle_exit_status(new_input, i));
	return (handle_var_expansion(new_input, input, i));
}

void	handle_var_value(char **new_input, char *var_value)
{
	if (var_value)
	{
		append_str(new_input, var_value);
		free(var_value);
	}
	else
		append_str(new_input, "");
}

int	handle_var_expansion(char **new_input, char *input, int *i)
{
	int		var_size;
	char	*var_name;
	char	*var_value;

	if (input[*i + 1] == '"')
		(*i)++;
	var_size = find_and_size_var_name(&input[*i]);
	if (var_size <= 0)
	{
		append_char(new_input, '$');
		(*i)++;
		return (1);
	}
	var_name = find_var_name2(&input[*i], var_size);
	if (!var_name)
		return (handle_var_not_found(new_input));
	var_value = find_var_in_env(input, var_name, msh()->env);
	handle_var_value(new_input, var_value);
	free(var_name);
	*i += var_size + 1;
	if (input[*i] == '"')
		(*i)++;
	if (input[*i - 1] == '"')
		(*i)--;
	return (1);
}
