/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 01:33:41 by msilva-c          #+#    #+#             */
/*   Updated: 2025/05/20 13:55:16 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_default_env(void)
{
	char	cwd[4096];
	char	**default_env;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		exit(1);
	}
	default_env = safe_malloc(sizeof(char *) * 4);
	default_env[0] = ft_strjoin("PWD=", cwd);
	default_env[1] = ft_strdup("SHLVL=1");
	default_env[2] = ft_strdup("_=/usr/bin/env");
	default_env[3] = NULL;
	return (default_env);
}

t_env	*empty_env(void)
{
	t_env	*start;
	t_env	*temp;
	char	**default_env;
	int		i;

	i = 0;
	start = NULL;
	default_env = get_default_env();
	while (default_env && default_env[i])
	{
		temp = create_var(default_env[i]);
		if (i > 0)
			var_add_back(start, temp);
		free(temp);
	}
	if (default_env)
		free_matrix(default_env);
	return (start);
}

t_env	*env_dup(t_env *env)
{
	t_env	*new;
	t_env	*temp;

	if (!env)
		return (NULL);
	new = create_var(env->var);
	temp = env->next;
	while (temp)
	{
		var_add_back(new, create_var(temp->var));
		temp = temp->next;
	}
	return (new);
}
