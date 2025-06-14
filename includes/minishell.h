/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:57:32 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 14:27:08 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include "structs.h"
# include "builtins.h"
# include "executor.h"
# include "expander.h"
# include "heredoc.h"
# include "parser.h"
# include "signs.h"
# include "utils.h"

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
# define HEREDOC_SYNT_ERR "minishell : syntax error \
near unexpected token `<<'\n"
# define MALLOC_FAIL "Error: Memory allocation failed in init_exec\n"

#endif
