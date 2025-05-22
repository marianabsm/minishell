/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:57:32 by marianamest       #+#    #+#             */
/*   Updated: 2025/05/20 14:22:11 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stddef.h>

# define NO_TYPE 0 
# define CMD 1
# define PIPE 2
# define R_OUT 3
# define R_APP 4
# define R_IN 5
# define HERE_DOC 6

# define PIPE_SYNT_ERR "minishell : syntax error near unexpected token `|'\n"
# define APP_SYNT_ERR "minishell : syntax error near unexpected token `>>'\n"
# define IN_SYNT_ERR "minishell : syntax error near unexpected token `>'\n"
# define OUT_SYNT_ERR "minishell : syntax error near unexpected token `<'\n"
# define HEREDOC_SYNT_ERR "minishell : syntax error near unexpected token `<<'\n"

typedef struct s_exec
{
	int		*pid;
	int		nbr_cmds;
	int		in_pipe_fd[2];
	int		out_pipe_fd[2];
	int		pipe_doc[2];
	int		index;
}					t_exec;

typedef struct s_env
{
	char			*var;
	char			*var_name;
	char			*var_value;
	int				valid;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	char			*content;
	int				type;
	int				index;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;


typedef struct s_simple_command
{
	int 			n_of_arg;
	char			*name;
	char			*path;
	char			**array_args;
	int 			input_fd;
	int 			output_fd;
}					t_simple_command;

typedef struct s_redirs_list
{
	int				redir_type;
	char			*file;
	char			*delimiter;
	int				heredoc_fd;
	int				expand_heredoc;
	struct s_redirs_list *next;
}					t_redirs_list;

typedef struct s_command_table
{
	t_simple_command	*simplecommand;
	t_redirs_list		*redirs;
	struct s_command_table *next;
}					t_command_table;

typedef struct s_msh
{
	char			*line;
	char			*home;
	char			*pwd;
	char			**env;
	t_token			*tokens;
	t_exec			*exec;
	t_command_table	*cmd_table;
	int				exit_status;
	bool			signaled;
}					t_msh;

# include "builtins.h"
# include "executor.h"
# include "expander.h"
# include "heredoc.h"
# include "parser.h"
# include "signs.h"
# include "utils.h"

#endif
