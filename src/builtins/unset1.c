/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:41:04 by marianamest       #+#    #+#             */
/*   Updated: 2025/03/21 18:03:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int if_var_exists(char *name)
{
	t_env *env;

	env = msh()->env;
	while(env)
	{	
		if(!ft_strcmp(name, env->var_name))
			return(1);
		env = env->next;
	}
	return(0);
}

void remove_var(char *name)
{
    t_env *env;
    t_env *temp;

    env = msh()->env;
    if (env && !ft_strcmp(env->var_name, name))
    {
        msh()->env = env->next;
        free(env->var_name);
        free(env->var_value);
        free(env);
        return;
    }
    while (env && env->next)
    {
        if (!ft_strcmp(env->next->var_name, name))
        {
            temp = env->next;
            env->next = env->next->next;
            free(temp->var_name);
            free(temp->var_value);
            free(temp);
            return;
        }
        env = env->next;
    }
}

void	exec_unset(char **args)
{
	int	i;

	if (!args || !msh()->env)
		return ;
	i = 1;
	while (args[i])
	{
		if(if_var_exists(args[i]))
			remove_var(args[i]);
		i++;
	}
	msh()->exit_status = 0;
}
