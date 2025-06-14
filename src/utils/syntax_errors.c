/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:14:22 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 22:46:23 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_fds(void)
{
	msh()->original_stdout = dup(STDOUT_FILENO);
	msh()->original_stdin = dup(STDIN_FILENO);
}

void	reset_fds(void)
{
	dup2(msh()->original_stdout, STDOUT_FILENO);
	dup2(msh()->original_stdin, STDIN_FILENO);
	close(msh()->original_stdout);
	close(msh()->original_stdin);
}

int	check_syntax_general(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == PIPE && (!tokens->prev || !tokens->next
				|| tokens->next->type == PIPE))
		{
			ft_putstr_fd(PIPE_SYNT_ERR, STDERR_FILENO);
			return (0);
		}
		if ((tokens->type == R_APP || tokens->type == R_IN
				|| tokens->type == R_OUT || tokens->type == HERE_DOC)
			&& (!tokens->next || tokens->next->type != CMD))
		{
			if (tokens->type == R_APP)
				ft_putstr_fd(APP_SYNT_ERR, STDERR_FILENO);
			if (tokens->type == R_IN)
				ft_putstr_fd(IN_SYNT_ERR, STDERR_FILENO);
			if (tokens->type == R_OUT)
				ft_putstr_fd(OUT_SYNT_ERR, STDERR_FILENO);
			if (tokens->type == HERE_DOC)
				ft_putstr_fd(HEREDOC_SYNT_ERR, STDERR_FILENO);
			return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}

char	*ft_strtrim(char *s, char c)
{
	int		start;
	int		end;
	char	*result;

	if (!s)
		return (NULL);
	start = 0;
	end = ft_strlen(s) - 1;
	while (s[start] && s[start] == c)
		start++;
	while (end > start && s[end] == c)
		end--;
	result = malloc(end - start + 2);
	if (!result)
		return (NULL);
	ft_strncpy(result, s + start, end - start + 1);
	result[end - start + 1] = '\0';
	return (result);
}

size_t	ft_strspn(const char *s, const char *accept)
{
	size_t	i;
	size_t	j;
	int		found;

	i = 0;
	while (s[i])
	{
		found = 0;
		j = 0;
		while (accept[j])
		{
			if (s[i] == accept[j])
			{
				found = 1;
				break ;
			}
			j++;
		}
		if (!found)
			break ;
		i++;
	}
	return (i);
}
