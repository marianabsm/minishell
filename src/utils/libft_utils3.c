/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 21:44:47 by msilva-c          #+#    #+#             */
/*   Updated: 2025/03/22 16:44:09 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isoperator(char *str, int i)
{
	if (str[i] == '>' && str[i + 1] == '>')
		return (2);
	else if (str[i] == '<' && str[i + 1] == '<')
		return (2);
	else if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	if (c == 32 || (c <= 13 && c >= 9))
		return (1);
	return (0);
}

int	ft_isalpha(char c)
{
	if ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A'))
		return (1);
	return (0);
}

int	ft_isdigit(char c)
{
	if (c <= '9' && c >= '0')
		return (1);
	return (0);
}

int	ft_isquote(char c)
{
	if (c == 39 || c == 34)
		return (1);
	else
		return (0);
}
