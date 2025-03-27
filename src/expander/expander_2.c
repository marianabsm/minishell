/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 20:53:02 by msilva-c          #+#    #+#             */
/*   Updated: 2025/03/19 15:26:54 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	var_name_len(char *str, int i)
{
	int	len;

	len = 0;
	if (!ft_isalpha(str[i]) && str[i] != 95)
		return (0);
	else if (ft_isdigit(str[i]))
		return (1);
	while (str[i + len] && str[i + len] != '$' && str[i + len] != TEMP_DOLLAR
		&& !ft_isquote(str[i + len]))
	{
		if (ft_isdigit(str[i + len]) || ft_isalpha(str[i + len])
			|| str[i + len] == '_')
			len++;
		else
			break ;
	}
	return (len);
}

char	*grep_var_name(t_token *token)
{
	char	*var_name;
	int		i;

	i = 0;
	while (token->content[i] != '$')
		i++;
	i++;
	if (token->content[i] == '$')
		var_name = ft_strdup("$$");
	else if (token->content[i] == '?')
		var_name = ft_strdup("$?");
	else
		var_name = ft_substr(token->content, i, var_name_len(token->content,
					i));
	return (var_name);
}

int	expanded_strlen(char *old, char *var_value)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (old[i] != '$')
		i++;
	len += i;
	i += var_name_len(old, i);
	while (old[i] != '\0')
	{
		i++;
		len++;
	}
	return (len + ft_strlen(var_value));
}
