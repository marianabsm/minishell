/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:18:18 by msilva-c          #+#    #+#             */
/*   Updated: 2025/06/10 17:20:43 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_home(void)
{
	char	*wd;
	char	*ret;
	int		i;
	int		count_slash;

	i = 0;
	count_slash = 0;
	wd = NULL;
	wd = getcwd(NULL, 0);
	while (wd[i] != '\0')
	{
		if (wd[i] == '/')
			count_slash++;
		if (count_slash == 3)
			break ;
		i++;
	}
	ret = safe_malloc(i + 1);
	ret[i] = '\0';
	while (--i >= 0)
		ret[i] = wd[i];
	free(wd);
	return (ret);
}

/* singleton */
t_msh	*msh(void)
{
	static t_msh	msh;

	return (&msh);
}

t_msh	*init_all(char **envp)
{
	msh()->line = NULL;
	msh()->cmd_table = NULL;
	msh()->tokens = NULL;
	msh()->env_list = init_env(envp);
	msh()->env = duplicate_envp(envp);
	msh()->home = get_home();
	msh()->pwd = getcwd(NULL, 0);
	msh()->exec = NULL;
	msh()->exit_status = 0;
	msh()->output = NULL;
	msh()->signaled = false;
	msh()->any = 0;
	return (msh());
}

t_env	*init_env(char **envp)
{
	t_env	*env_list;
	t_env	*new_node;
	int		i;

	i = 0;
	env_list = NULL;
	while (envp[i])
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (NULL);
		new_node->var = ft_strdup(envp[i]);
		new_node->var_name = ft_struntil(envp[i], '=');
		new_node->var_value = ft_strafter(envp[i], '=');
		new_node->valid = 1;
		new_node->next = env_list;
		env_list = new_node;
		i++;
	}
	return (env_list);
}
