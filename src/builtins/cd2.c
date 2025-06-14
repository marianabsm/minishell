/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:10:19 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 14:10:20 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_env(char *key, char *value)
{
	int		i;
	char	*new_var;
	size_t	key_len;

	i = 0;
	if (!key || !value)
		return ;
	key_len = ft_strlen(key);
	new_var = ft_strjoin3(key, "=", value);
	while (msh()->env && msh()->env[i])
	{
		if (ft_strncmp(msh()->env[i], key, key_len) == 0
			&& msh()->env[i][key_len] == '=')
		{
			free(msh()->env[i]);
			msh()->env[i] = new_var;
			return ;
		}
		i++;
	}
	msh()->env = add_to_env(msh()->env, new_var);
	free(new_var);
}

void	change_dir(char **args)
{
	printf("Error changing directory to: %s\n", args[1]);
	ft_putstr_fd("minishell: cd: ", 2);
	perror(args[1]);
	msh()->exit_status = 1;
}

void	cd_home(char *home)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (home)
		perror(home);
	else
		perror("HOME not set");
	msh()->exit_status = 1;
	free(home);
}

void	getcwd_error(void)
{
	perror("getcwd");
	msh()->exit_status = 1;
}

int	count_args(char **args)
{
	int	argc;

	argc = 0;
	while (args[argc])
		argc++;
	return (argc);
}
