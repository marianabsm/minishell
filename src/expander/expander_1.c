/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:25:45 by msilva-c          #+#    #+#             */
/*   Updated: 2025/03/20 07:44:41 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_edge_expand(char *var_name)
{
	if (!var_name || !*var_name)
		return (0);
	else if (ft_strlen(var_name) != 2)
		return (0);
	else if (var_name[0] == '$')
	{
		if (var_name[1] == '?' || var_name[1] == '?')
			return (1);
	}
	return (0);
}

// rever ilegal ft getpid()
char	*edge_expand(char *var_name, t_msh *msh)
{
	char	*var_value;

	var_value = ft_strdup("");
	if (ft_strlen(var_name) != 2)
		return (var_value);
	else if (var_name[1] == '?')
	{
		free(var_value);
		var_value = ft_itoa(msh->exit_status);
	}
	else if (var_name[1] == '$')
	{
		free(var_value);
		var_value = ft_strdup("");
	}
	return (var_value);
}

char	*regular_expand(t_env *env, char *var_name)
{
	char	*var_value;

	var_value = ft_strdup("");
	if (!env || !var_name || !*var_name)
		return (var_value);
	while (env)
	{
		if (!ft_strcmp(var_name, env->var_name))
		{
			free(var_value);
			var_value = ft_strdup(env->var_value);
			break ;
		}
		env = env->next;
	}
	return (var_value);
}

// rever expanded strlen, var_name_len e o if else
char	*update_content(t_token *token, char *old, char *expanded)
{
	char	*new;
	int		x;
	int		y;
	int		z;

	(void)token;
	x = 0;
	y = 0;
	z = 0;
	new = (char *)safe_malloc(sizeof(char) * (expanded_strlen(old, expanded)
				+ 1));
	while (old[x] != '$')
		new[y++] = old[x++];
	while (expanded[z])
		new[y++] = expanded[z++];
	if (old[x + 1] == '$' || old[x + 1] == '?')
		x += 2;
	else
		x += var_name_len(old, x + 1) + 1;
	while (old[x])
		new[y++] = old[x++];
	new[x] = '\0';
	// REVER NAO E RETURN 0 CARALHO
	return (0);
}

void	expander(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp)
	{
		ignore_dollar(temp->content);
		if (needs_expansion(temp))
			expand_var(temp, msh());
		else
		{
			put_dollar_back(temp->content);
			temp = temp->next;
		}
	}
}
