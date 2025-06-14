/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 00:04:58 by  marianames       #+#    #+#             */
/*   Updated: 2025/06/05 15:01:47 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "../includes/minishell.h"

/* run_doc.c */
int		run_doc(t_command_table *table, t_redirs_list *redir);
void	read_into_heredoc(t_redirs_list *redir, int pipe_doc[2]);
void	write_to_pipe(char *str, int fd);

/* waitpid.c */
void	close_pipe(int *fd);
void	safe_close(int fd);

#endif
