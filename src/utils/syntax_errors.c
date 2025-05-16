/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:14:22 by marianamest       #+#    #+#             */
/*   Updated: 2025/04/02 21:04:14 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_syntax_pipes(char *str)
{
    int i;
    
    i = 0;
    while (str && ft_isspace(str[i]))
        i++;
    if (!str[i] || str[i] == '|')
    {
        ft_put_str_fd("minishell : syntax error near unexpected token `|'\n", STDERR_FILENO);
        return (0);
    }
    while (str && str[i] != '\0')
    {
        if (str[i] == '|')
        {
            int j = i - 1;
            while (j >= 0 && ft_isspace(str[j]))
                j--;
            if (j >= 0 && (str[j] == '<' || str[j] == '>'))
            {
                ft_put_str_fd("minishell : syntax error near unexpected token `|'\n", STDERR_FILENO);
                return (0);
            }
            j = i + 1;
            while (str[j] && ft_isspace(str[j]))
                j++;
            if (str[j] == '|')
            {
                ft_put_str_fd("minishell : syntax error near unexpected token `|'\n", STDERR_FILENO);
                return (0);
            }
        }
        i++;
    }
    i = ft_strlen(str) - 1;
    while (i >= 0 && ft_isspace(str[i]))
        i--;
    if (i >= 0 && str[i] == '|')
    {
        ft_put_str_fd("minishell : syntax error near unexpected token `|'\n", STDERR_FILENO);
        return (0);
    }
    return (1);
}

int check_syntax_redirs1(char *str)
{
    int i;
    
    i = 0;
    while (str && str[i] != '\0')
    {
        if (str[i] == '>')
        {
            if (str[i + 1] == '>')
            {
                if (str[i + 2] == '>' || str[i + 2] == '<')
                {
                    ft_put_str_fd("minishell : syntax error near unexpected token `>'\n", STDERR_FILENO);
                    return (0);
                }
                i++;
            }
            else if (str[i + 1] == '<')
            {
                ft_put_str_fd("minishell : syntax error near unexpected token `>'\n", STDERR_FILENO);
                return (0);
            }
            i++;
            while (str[i] && ft_isspace(str[i]))
                i++;
            if (str[i] == '>' || str[i] == '<')
            {
                ft_put_str_fd("minishell : syntax error near unexpected token `>'\n", STDERR_FILENO);
                return (0);
            }
        }
        i++;
    }
    i = ft_strlen(str) - 1;
    while (i >= 0 && ft_isspace(str[i]))
        i--;
    if (i >= 0 && str[i] == '>')
    {
        ft_put_str_fd("minishell : syntax error near unexpected token `>'\n", STDERR_FILENO);
        return (0);
    }
    return (1);
}

int check_syntax_redirs2(char *str)
{
    int i;
    
    i= 0;
    while (str && str[i] != '\0')
    {
        if (str[i] == '<')
        {
            if (str[i + 1] == '<')
            {
                if (str[i + 2] == '<' || str[i + 2] == '>')
                {
                    ft_put_str_fd("minishell : syntax error near unexpected token `<'\n", STDERR_FILENO);
                    return (0);
                }
                i++;
            }
            else if (str[i + 1] == '>')
            {
                ft_put_str_fd("minishell : syntax error near unexpected token `<'\n", STDERR_FILENO);
                return (0);
            }
            i++;
            while (str[i] && ft_isspace(str[i]))
                i++;
            if (str[i] == '<' || str[i] == '>')
            {
                ft_put_str_fd("minishell : syntax error near unexpected token `<'\n", STDERR_FILENO);
                return (0);
            };
        }
        i++;
    }
    i = ft_strlen(str) - 1;
    while (i >= 0 && ft_isspace(str[i]))
        i--;
    if (i >= 0 && str[i] == '<')
    {
        ft_put_str_fd("minishell : syntax error near unexpected token `<'\n", STDERR_FILENO);
        return (0);
    }
    return (1);
}

int check_syntax_general(char *str)
{
    if (!str)
        return (0);
    if (check_syntax_pipes(str) && check_syntax_redirs1(str) && check_syntax_redirs2(str))
        return (1);
    return (0);
}

