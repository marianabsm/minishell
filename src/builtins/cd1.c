/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:40:50 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 01:15:04 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	change_to_home(void)
{
	char	*home;
	int		ret;

	home = get_home();
	ret = 0;
	if (!home || chdir(home) != 0)
	{
		cd_home(home);
		ret = -1;
	}
	else
		free(home);
	return (ret);
}

static int	change_to_path(char *path, char **args)
{
	if (chdir(path) != 0)
	{
		change_dir(args);
		return (-1);
	}
	return (0);
}

static int	update_pwd_env(void)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		getcwd_error();
		return (-1);
	}
	set_env("PWD", cwd);
	return (0);
}

void	cd(char **args)
{
	int	argc;

	argc = count_args(args);
	if (argc > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		msh()->exit_status = 1;
		return ;
	}
	if (!args[1])
	{
		if (change_to_home() != 0)
			return ;
	}
	else
	{
		if (change_to_path(args[1], args) != 0)
			return ;
	}
	if (update_pwd_env() != 0)
		return ;
	msh()->exit_status = 0;
}
