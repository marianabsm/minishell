/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 00:04:58 by marianamest       #+#    #+#             */
/*   Updated: 2025/03/22 15:47:32 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "../includes/minishell.h"

char	**ft_split(char const *str, char c);
size_t	ft_strlcat(char *dst, const char *src, size_t n);


/* prep_redir.c */
int     prep_in_redir(t_exec *exec);
int     doc_loop(char **in_redirs, t_exec *exec, int k);
int     open_infile_loop(char **in_redirs, t_exec *exec, int k);
int     is_final_heredoc(char **in_redirs, t_exec *exec, int k);
bool    check_and_open_file(char *file_name);

/* run_doc.c */
int     run_doc(char *delimiter, t_exec *exec, int k);
void    read_into_heredoc(char *delimiter, t_exec *exec, int k);
void    control_d_handle(t_exec *exec, int k, char *str);
void    write_to_pipe(char *str, t_exec *exec);

/* waitpid.c */
void    close_pipe(int *fd);
void    safe_close(int fd);

#endif
