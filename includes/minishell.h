/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:57:32 by marianamest       #+#    #+#             */
/*   Updated: 2025/03/22 16:36:06 by msilva-c         ###   ########.fr       */
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

//echo "ola" > test.c | wc -l
//exec[0].args[0] = echo
//exec[0].args[1] = ola
//exec[0].args[2] = >
//exec[0].args[3] = test.c
//exec[0].args[4] = NULL
//
//exec[1].args[0] = wc
//exec[1].args[1] = -l
//exec[1].args[2] = NULL

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

// rever: criar uma ft que transforma linked list em char **
typedef struct s_msh
{
	char			*line;
	char			*home;
	char			*pwd;
	t_env			*env;
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
