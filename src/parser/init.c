/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:18:18 by msilva-c          #+#    #+#             */
/*   Updated: 2025/05/19 15:56:03 by marianamest      ###   ########.fr       */
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

t_msh	*init_all(char **envp) // aqui
{
	msh()->line = NULL;
	msh()->cmd_table = NULL;
	msh()->tokens = NULL;
	// get_env(envp);
	msh()->env = duplicate_envp(envp);
	msh()->home = get_home();
	msh()->pwd = getcwd(NULL, 0);
	msh()->exec = NULL;
	msh()->exit_status = 0;
	msh()->signaled = false;
	return (msh());
}
