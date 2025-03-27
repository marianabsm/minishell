/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quotes1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 04:54:10 by msilva-c          #+#    #+#             */
/*   Updated: 2025/03/22 00:56:09 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
int rm_strlen(char *line)
{
	int i;
	int singleq;
	int doubleq;

	i = 0;
	singleq = 0;
	doubleq = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] == 39 && doubleq % 2 == 0)
			singleq += 1;
		else if (line[i] == 34 && singleq % 2 == 0)
			doubleq += 1;
		i++;
	}
	return (singleq + doubleq);
}

char *rm_quote(char *str)
{
	char *new;
	int size_new;
	int i;
	int j;
	i = 0;
	j = 0;
	size_new = ft_strlen(str);
	size_new = size_new - rm_strlen(str);

	if (!rm_strlen(str))
		return (str);
	new = (char *)safe_malloc((size_new) + 1);
	while(i < ft_strlen(str) && j < size_new)
	{
		if (ft_isquote(str[i]) && !in_quotes(str, i))
			i++;
		else if (ft_isquote(str[i]) && !in_quotes(str, i) && i > 0 && in_quotes(str, i - 1))
			i++;
		else
		{
			new[j++] = str[i++];

		}
	}
	//new[j] == '\0';
	free(str);
	printf("%s\n", new);
	return (new);
}


void	rm_quotes_exec(void)
{
	int		i;
	int index;
	t_exec *exec;

	i = 0;
	index = 0;
	exec = msh()->exec;
	if (!exec)
		return ;
	while (index < exec->nbr_cmds)
	{
		while (exec[index].args && exec[index].args[i])
		{
			exec[index].args[i] = rm_quote(exec[index].args[i]);
			i++;
		}
		index++;
	}
}
