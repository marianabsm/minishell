/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signs.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:26:02 by marianamest       #+#    #+#             */
/*   Updated: 2025/03/20 16:22:49 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNS_H
# define SIGNS_H

# include "../includes/minishell.h"

/* src/signals/signals_1.c */
void    main_signals(void);
void	sigint_handler(int sig);
void    signals_parent(void);
void    signals_ignore(void);
void    signals_default(void);

/* src/signals/signals_2.c */
void    handle_signaled(int status);
void    ft_waitpid(int pid);

#endif
