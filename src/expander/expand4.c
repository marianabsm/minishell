/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:11:38 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 14:11:39 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_weird(char *input)
{
	if ((input[0] == '$' && input[1] == '\'') || (input[0] == '$'
			&& input[1] == '"') || (input[0] == '\'' && input[ft_strlen(input)
				- 1] == '\''))
		return (1);
	return (0);
}

int	handle_exit_status(char **new_input, int *i)
{
	char	*itoa_str;
	char	*temp;

	itoa_str = ft_itoa(msh()->exit_status);
	temp = ft_strjoin(*new_input, itoa_str);
	free(*new_input);
	*new_input = temp;
	free(itoa_str);
	*i += 2;
	return (1);
}

void	append_char(char **new_input, char c)
{
	char	*temp;

	temp = ft_strjoin_char(*new_input, c);
	free(*new_input);
	*new_input = temp;
}

void	append_str(char **dst, const char *src)
{
	char	*tmp;

	tmp = ft_strjoin(*dst, src);
	free(*dst);
	*dst = tmp;
}

int	handle_var_not_found(char **new_input)
{
	free(*new_input);
	*new_input = ft_strdup("");
	return (0);
}
