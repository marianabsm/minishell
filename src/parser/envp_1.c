/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 01:27:31 by msilva-c          #+#    #+#             */
/*   Updated: 2025/06/05 15:21:25 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	dup_var(t_env *start, t_env *new)
{
	t_env	*temp;

	temp = start;
	while (temp)
	{
		if (!ft_strcmp(temp->var_name, new->var_name))
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	var_add_back(t_env *start, t_env *new)
{
	t_env	*temp;
	t_env	*end;

	end = NULL;
	temp = start;
	if (new->valid == false && dup_var(temp, end))
		return ;
	while (temp)
	{
		if (!ft_strcmp(temp->var_name, new->var_name))
		{
			free(temp->var_value);
			temp->var_value = ft_strdup(new->var_value);
			temp->valid = true;
			free_var(new);
			return ;
		}
		end = temp;
		temp = temp->next;
	}
	if (end)
		end->next = new;
}

t_env	*create_var(const char *arg)
{
	t_env	*new_var;
	char	*equal_sign;

	new_var = (t_env *)safe_malloc(sizeof(t_env));
	if (!new_var)
		return (NULL);
	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		new_var->var_name = ft_substr(arg, 0, equal_sign - arg);
		new_var->var_value = ft_strdup(equal_sign + 1);
	}
	else
	{
		new_var->var_name = ft_strdup(arg);
		new_var->var_value = NULL;
	}
	new_var->valid = 1;
	new_var->next = NULL;
	return (new_var);
}

int	check_env(char **envp)
{
	int	i;

	i = 0;
	if (!envp || !*envp)
		return (0);
	while (envp[i])
		i++;
	return (i);
}
