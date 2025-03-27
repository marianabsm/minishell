/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:40:50 by marianamest       #+#    #+#             */
/*   Updated: 2025/03/21 18:13:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd(char **args, int fd)
{
	char	env_var[4128];
	char	cwd[4096];
	char	*home;
	(void)fd;
	
	if(!args) // go back to root
	{
		home = get_home();
		chdir(home);
		free(home);
		return ;
	}
	if (!args || chdir(args[1]))
	{
		write(2, "minishell: cd ", 14);
		perror(args[1]);
		msh()->exit_status = 1;
		return ;
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("get cwd error.");
		msh()->exit_status = 1;
		return ;
	}
	ft_strlcpy(env_var, "PWD=", sizeof(env_var));
	ft_strlcat(env_var, cwd, sizeof(env_var));
	update_pwd(); // updates the pwd env var internally within shell's env struct
	//export((char *[]){"export", env_var, NULL}, fd); // ensures that the updated PWD var 
	// is also reflected in the shell's environment
	// that is accessible to child processes and external commands
	msh()->exit_status = 0;
}
