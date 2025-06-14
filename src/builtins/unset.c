/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:41:04 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/08 21:09:04 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	if_var_exists(char *name)
{
	t_env	*env;

	env = msh()->env_list;
	while (env)
	{
		if (!ft_strcmp(name, env->var_name))
			return (1);
		env = env->next;
	}
	return (0);
}

static void	free_for_unset(t_env *env)
{
	free(env->var_name);
	free(env->var_value);
	free(env);
}

void	remove_var(char *name)
{
	t_env	*env;
	t_env	*temp;

	env = msh()->env_list;
	if (env && !ft_strcmp(env->var_name, name))
	{
		msh()->env_list = env->next;
		free_for_unset(env);
		return ;
	}
	while (env && env->next)
	{
		if (!ft_strcmp(env->next->var_name, name))
		{
			temp = env->next;
			env->next = env->next->next;
			free_for_unset(temp);
			if (msh()->env)
				free_matrix(msh()->env);
			msh()->env = update_env_matrix(msh()->env_list);
			return ;
		}
		env = env->next;
	}
}

void	exec_unset(char **args)
{
	t_env	*env;
	t_env	*prev;

	if (!args[1])
		return ;
	env = msh()->env_list;
	prev = NULL;
	while (env)
	{
		if (ft_strcmp(env->var_name, args[1]) == 0)
		{
			if (prev)
				prev->next = env->next;
			else
				msh()->env_list = env->next;
			free_for_unset(env);
			break ;
		}
		prev = env;
		env = env->next;
	}
	if (msh()->env)
		free_matrix(msh()->env);
	msh()->env = update_env_matrix(msh()->env_list);
}
