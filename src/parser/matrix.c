/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:13:34 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 22:51:37 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	assign(const char *content, t_token *new_token)
{
	if (ft_strcmp(content, "|") == 0)
		new_token->type = PIPE;
	else if (ft_strcmp(content, ">") == 0)
		new_token->type = R_OUT;
	else if (ft_strcmp(content, ">>") == 0)
		new_token->type = R_APP;
	else if (ft_strcmp(content, "<") == 0)
		new_token->type = R_IN;
	else if (ft_strcmp(content, "<<") == 0)
		new_token->type = HERE_DOC;
	else
		new_token->type = CMD;
}

t_token	*create_token(const char *content, int index)
{
	t_token	*new_token;

	if (!content || content[0] == '\0')
		return (NULL);
	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->content = ft_strdup(content);
	if (!new_token->content)
	{
		free(new_token);
		return (NULL);
	}
	assign(content, new_token);
	new_token->index = index;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

void	add_token_to_list(t_token **head, t_token *new_token)
{
	t_token	*temp;

	if (!*head)
	{
		*head = new_token;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_token;
	new_token->prev = temp;
}

static int	create_and_append_token(t_token **tokens, char *content, int index)
{
	t_token	*new_token;

	new_token = create_token(content, index);
	if (!new_token)
		return (0);
	add_token_to_list(tokens, new_token);
	return (1);
}

t_token	*matrix_to_tokens(char **matrix)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (matrix[i])
	{
		if (matrix[i][0] != '\0' && strspn(matrix[i],
				" \t\n\r") != ft_strlen3(matrix[i]))
		{
			if (!create_and_append_token(&tokens, matrix[i], i))
			{
				free_token_list(tokens);
				tokens = NULL;
				return (NULL);
			}
		}
		i++;
	}
	return (tokens);
}
