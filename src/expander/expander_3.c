/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:44:20 by msilva-c          #+#    #+#             */
/*   Updated: 2025/03/22 16:28:27 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	needs_expansion(t_token *token)
{
	int	i;

	if (!token || !token->content || !token->content[0])
		return (0);
	if (token->content[0] == '$' && !token->content[1])
		return (0);
	i = 0;
	while (token->content[i])
	{
		if (token->prev && token->prev->type == HERE_DOC)
			return (0);
		if (token->content[i] == '$' && !in_singles(token->content, i))
			return (1);
		i++;
	}
	return (0);
}

void	expand_var(t_token *token, t_msh *msh)
{
	char	*var_name;
	char	*var_value;
	char	*updated;

	var_name = grep_var_name(token);
	if (is_edge_expand(var_name))
		var_value = edge_expand(var_name, msh);
	else
		var_value = regular_expand(msh->env, var_name);
	updated = update_content(token, token->content, var_value);
	free(token->content);
	token->content = updated;
	free(var_name);
	free(var_value);
}



void	ignore_dollar(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i] && i < ft_strlen(str))
	{
		if (str[i] == '$' && in_singles(str, i))
			str[i] = TEMP_DOLLAR;
		else if (str[i] == '$' && !str[i + 1] && i > 0 && str[i - 1] != '$')
			str[i] = TEMP_DOLLAR;
		else if (str[i] == '$' && str[i + 1] == 34 && in_quotes(str, i))
			str[i] = TEMP_DOLLAR;
		else if (str[i] == '$' && str[i + 1] == 39 && in_quotes(str, i + 1))
			str[i] = TEMP_DOLLAR;
		i++;
	}
}

void	put_dollar_back(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
	{
		if (str[i] == TEMP_DOLLAR)
			str[i] = '$';
	}
}
