/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:08:55 by msilva-c          #+#    #+#             */
/*   Updated: 2025/05/21 14:15:26 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_cmds(t_token *tokens)
{
	int nbr_cmds;
	nbr_cmds = 0;
	if (!tokens)
		return (0);
	while (tokens)
	{
		if (tokens->type == PIPE)
			nbr_cmds++;
		tokens = tokens->next;
	}
	return (nbr_cmds + 1);
}

int	strlen_args(char **args)
{
	int i = 0;
	if (args)
	{
		while (args[i])
			i++;
	}
	return i;
}
char **add_to_matrix(char *content, char **args)
{
    int i = 0;
    int new_size = strlen_args(args) + 2; // +1 for new string, +1 for NULL
    char **new = safe_malloc(sizeof(char *) * new_size);

    while (args && args[i])
    {
        new[i] = args[i]; // Reuse existing pointers
        i++;
    }
    new[i++] = ft_strdup(content);
    new[i] = NULL;
    free(args); // Free the old matrix
    return (new);
}
// char **add_to_matrix(char *content, char **args)
// {
// 	int i;
// 	int new_i;
// 	char **new;
// 	i = 0;
// 	new_i = -1;
// 	if (!args)
// 	{
// 		new = safe_malloc(sizeof(char *) * 2);
// 		new[0] = ft_strdup(content);
// 		new[1] = NULL;
// 	}
// 	else
// 	{
// 		i = strlen_args(args) + 1; //+1 is for the new str
// 		new = safe_malloc(sizeof(char *) * (i + 1)); //+1 is for null
// 		while (args[++new_i])
// 			new[new_i] = ft_strdup(args[new_i]);
// 		new[new_i] = ft_strdup(content);
// 		new[++new_i] = NULL;
// 	}
// 	free_matrix(args);
// 	return (new);
// }

void tokens_to_exec(t_token *token, t_exec *exec, int nbr_cmds)
{
    int i = 0;

    while (token)
    {
        exec[i].index = i;
        exec[i].nbr_cmds = nbr_cmds;
        exec[i].args = NULL; // Initialize args to NULL

        if (token->type != PIPE)
            exec[i].args = add_to_matrix(token->content, exec[i].args);

        if (token->type == PIPE)
            i++;

        token = token->next;
    }
}

t_exec *init_exec(t_token *tokens)
{
    t_exec *exec;
    int nbr_cmds;

    if (!tokens)
    {
        fprintf(stderr, "Error: tokens is NULL in init_exec\n");
        return (NULL);
    }

    nbr_cmds = count_cmds(tokens);
    exec = (t_exec *)malloc(sizeof(t_exec) * (nbr_cmds + 1));
    if (!exec)
    {
        fprintf(stderr, "Error: Memory allocation failed in init_exec\n");
        return (NULL);
    }

    tokens_to_exec(tokens, exec, nbr_cmds);
    return (exec);
}


int set_exec(void)
{
    t_token *tokens = msh()->tokens;

    if (!tokens)
    {
        fprintf(stderr, "Error: msh()->tokens is NULL in set_exec\n");
        return (0);
    }

    msh()->exec = init_exec(tokens);
    if (!msh()->exec)
    {
        fprintf(stderr, "Error: init_exec failed in set_exec\n");
        return (0);
    }
    return (1);
}