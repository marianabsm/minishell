/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signs.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:26:02 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 21:29:41 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNS_H
# define SIGNS_H

# include "../includes/minishell.h"

/* src/signals/signals_1.c */
void	main_signals(void);
void	sigint_handler(int sig);
void	signals_parent(void);
void	signals_ignore(void);
void	signals_default(void);

/* src/signals/signals_2.c */
void	handle_signaled(int status);
void	ft_waitpid(int pid);
void	sigquit_handler(int signo);

#endif
