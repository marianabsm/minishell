/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:47:08 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/09 12:52:17 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_env_global(void)
{
	if (msh()->env)
		free_matrix(msh()->env);
	msh()->env = update_env_matrix(msh()->env_list);
}

static void	error_export(char *arg, int fd)
{
	ft_putstr_fd("export: '", fd);
	ft_putstr_fd(arg, fd);
	ft_putstr_fd("': not a valid identifier\n", fd);
	msh()->exit_status = 1;
}

static int	handle_export_arg(char *arg, t_env *env, int fd)
{
	t_env	*new_var;

	if (!parse_export(arg))
	{
		error_export(arg, fd);
		return (0);
	}
	new_var = create_var(arg);
	if (!new_var)
		return (0);
	var_add_back(env, new_var);
	return (1);
}

static void	handle_export_args(char **args, t_env *env, int fd, int *changed)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (handle_export_arg(args[i], env, fd))
			*changed = 1;
		i++;
	}
}

void	export_command(char **args, t_env *env, int fd)
{
	int	changed;

	changed = 0;
	if (!args[1])
	{
		print_sorted_env(env, fd);
		return ;
	}
	handle_export_args(args, env, fd, &changed);
	if (changed && msh()->env_list)
		update_env_global();
}
