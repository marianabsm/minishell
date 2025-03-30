/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:12:58 by marianamest       #+#    #+#             */
/*   Updated: 2025/03/30 22:17:17 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_isspace2(int k)
{
    if(k == ' ')
        return(1);
    return(0);
}

int count_words2(const char *str)
{
    int count;
    int in_word;

    count = 0;
    in_word = 0;
    while (*str) {
        if (!ft_isspace2(*str) && !in_word)
        {
            in_word = 1;
            count++;
        }
        else if (ft_isspace2(*str))
            in_word = 0;
        str++;
    }
    return (count);
}

char *ft_substr(const char *str, int start, int len) 
{
    char *sub;

    sub = (char *)malloc(len + 1);
    if (!sub)
        return (NULL);
    strncpy(sub, str + start, len);
    sub[len] = '\0';
    return (sub);
}

static char *extract_next_token(const char *input, int *i) // 27 lines
{
    int start;
    char *token;

    if (input[*i] == '"') 
    {
        start = ++(*i);
        while (input[*i] && input[*i] != '"') 
            (*i)++;
        token = ft_substr(input, start, *i - start);
        if (input[*i] == '"') 
            (*i)++;
        return (token);
    }
    else if (input[*i] == '\'')
    {
        start = ++(*i);
        while (input[*i] && input[*i] != '\'') 
            (*i)++;
        token = ft_substr(input, start, *i - start);
        if (input[*i] == '\'') 
            (*i)++;
        return (token);
    }
    start = *i;
    while (input[*i] && !ft_isspace2(input[*i]) && input[*i] != '"' && input[*i] != '\'') 
        (*i)++;
    return (ft_substr(input, start, *i - start));
}

char **split_by_spaces(const char *input) 
{
    int word_count;
    char **matrix;
    int i;
    int k;

    i = 0;
    k = 0;
    if (!input) 
        return NULL;
    word_count = count_words2(input);
    matrix = (char **)malloc((word_count + 1) * sizeof(char *));
    if (!matrix)
        return NULL;
    while (input[i]) 
    {
        if (!ft_isspace2(input[i]))
            matrix[k++] = extract_next_token(input, &i);
        else
            i++;
    }
    matrix[k] = NULL;
    return (matrix);
}

// int main(void)
// {
//     const char *test_input;
//     char **result;
//     int i; 
//     test_input = "This is a \"'\"test string\"'\" 'for split_by_spaces.'";
//     result = split_by_spaces(test_input);
//     if (!result) 
//     {
//         printf("Error: split_by_spaces returned NULL.\n");
//         return (1);
//     }
//     printf("Words in the input string:\n");
//     for (i = 0; result[i] != NULL; i++) 
//     {
//         printf("Word %d: %s\n", i + 1, result[i]);
//         free(result[i]);
//     }
//     free(result);
//     return (0);
// }