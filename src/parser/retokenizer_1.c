/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retokenizer_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 04:46:51 by msilva-c          #+#    #+#             */
/*   Updated: 2025/03/22 16:54:57 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * example:
 * token->content=">>test.txt|cat"
 */
t_token	*get_operator(t_token *t)
{
	char	*temp;
	t_token	*op;
	t_token	*remain;

	temp = ft_substr(t->content, 0, ft_isoperator(t->content, 0));
	//printf("get_op = %s\n", temp);
	op = init_token(temp);
	free(temp);
	temp = ft_substr(t->content, ft_isoperator(t->content, 0),
			ft_strlen(t->content));
	//printf("get_remain = %s\n", temp);
	remain = init_token(temp);
	free(temp);
	remain->prev = op;
	op->next = remain;
	return (op);
}

/*
 * example:
 * token->content="ola|"
 */
t_token	*get_word(t_token *t)
{
	int		i;
	char	*temp;
	t_token	*word;
	t_token	*remain;

	i = 0;
	while (t->content[i] && ((ft_isoperator(t->content, i) > 0
				&& in_quotes(t->content, i)) || ft_isoperator(t->content,
				i) == 0))
		i++;
	temp = ft_substr(t->content, 0, i);
	//printf("get_op = %s\n", temp);
	word = init_token(temp);
	free(temp);
	temp = ft_substr(t->content, i, ft_strlen(t->content));
	//printf("get_remain = %s\n", temp);
	remain = init_token(temp);
	free(temp);
	word->next = remain;
	word->next->prev = word;
	return (word);
}

int	needs_retoken(char *cmd)
{
	int		i;
	bool	operator;
	bool	word;

	i = -1;
	operator = false;
	word = false;
	if (!cmd)
		return 0;
	while (cmd && cmd[++i])
	{
		if (ft_isoperator(cmd, i) && !in_quotes(cmd, i))
			operator = true;
		else
			word = true;
	}
	if (ft_strlen(cmd) > ft_isoperator(cmd, 0) && operator)
		return (1);
	else if (operator && word)
		return (1);
	return (0);
}

t_token	*get_which(t_token *old)
{
	t_token	*new;

	new = NULL;
	if (ft_isoperator(old->content, 0) > 0)
		new = get_operator(old);
	else
		new = get_word(old);
	return (new);
}

t_token *update_token(t_token *old)
{
	t_token	*new;


	new = get_which(old);
	new->next->next = old->next;
	if(old->prev != NULL)
		old->prev->next = new;
	new->prev = old->prev;
	if (old->next)
		old->next->prev = new->next;
	free(old);
	return (new);
}
