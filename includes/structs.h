/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:14:04 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 17:59:14 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "../includes/minishell.h"

typedef struct s_quote_state
{
	int						in_single;
	int						in_double;
	int						i;
}							t_quote_state;

typedef struct s_exec
{
	int						*pid;
	int						nbr_cmds;
	int						in_pipe_fd[2];
	int						out_pipe_fd[2];
	int						pipe_doc[2];
	int						index;
}							t_exec;

typedef struct s_env
{
	char					*var;
	char					*var_name;
	char					*var_value;
	int						valid;
	struct s_env			*next;
}							t_env;

typedef struct s_token
{
	char					*content;
	int						type;
	int						index;
	struct s_token			*next;
	struct s_token			*prev;
}							t_token;

typedef struct s_simple_command
{
	int						n_of_arg;
	char					*name;
	char					*path;
	char					**array_args;
	int						input_fd;
	int						output_fd;
}							t_simple_command;

typedef struct s_redirs_list
{
	int						redir_type;
	char					*file;
	char					*delimiter;
	int						heredoc_fd;
	int						expand_heredoc;
	struct s_redirs_list	*next;
}							t_redirs_list;

typedef struct s_command_table
{
	t_simple_command		*simplecommand;
	t_redirs_list			*redirs;
	struct s_command_table	*next;
}							t_command_table;

typedef struct s_msh
{
	char					*line;
	char					*home;
	char					*pwd;
	char					**env;
	t_env					*env_list;
	t_token					*tokens;
	t_exec					*exec;
	t_command_table			*cmd_table;
	int						exit_status;
	char					*output;
	bool					signaled;
	int						original_stdin;
	int						original_stdout;
	int						any;
}							t_msh;

#endif