/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:57:32 by marianamest       #+#    #+#             */
/*   Updated: 2025/04/04 15:51:38 by marianamest      ###   ########.fr       */
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

# define CMD 1
# define PIPE 2
# define R_OUT 3
# define R_APP 4
# define R_IN 5
# define HERE_DOC 6

// rever se ainda vai ser preciso dps da ft_dup_env - Environment variables

typedef struct s_exec
{
	int		pid;
	char 	**args;
	int		nbr_cmds; //pipes
	int		pipe_fd[2];
	int		pipe_doc[2];
	int		in_fd;
	int		out_fd;
	bool	is_heredoc;
	char	**envp; // manter a t_env e arranjar uma função
	bool	cmd_invalid;
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
	char			*content; // a palavra ou simbolo
	int				type; // pavra pipe ou redir
	int				index; // o johny nao usou mas seria o index na matrix
	struct s_token	*next; // o prox token
	struct s_token	*prev; // johny nao usou mas self explanatory
}					t_token;

/////////////////////////////////////// from here ///////////////////////////////////////

typedef struct s_simple_command
{
	int 			n_of_arg;
	char			**array_args;
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
	int					shellvl; // rever : a ver com johny
	t_simple_command	*simplecommand;
	t_redirs_list		*redirs;
	struct s_command_table *next;
}					t_command_table;

//////////////////////////////////////// to here ////////////////////////////////////////

typedef struct s_msh
{
	char			*line;
	char			*home;
	char			*pwd;
	//t_env			*env;
	char			**env; // aqui
	t_token			*tokens;
	t_exec			*exec;
	int				exit_status;
	bool			signaled;
}					t_msh;

typedef enum e_temp_op
{
	TEMP_DOLLAR = -1,
	TEMP_PIPE = -2,
	TEMP_IN = -3,
	TEMP_OUT = -4,
}					t_temp_op;


# include "builtins.h"
# include "executor.h"
# include "expander.h"
# include "heredoc.h"
# include "parser.h"
# include "signs.h"
# include "utils.h"

#endif
