/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:21:23 by marianamest       #+#    #+#             */
/*   Updated: 2025/03/28 18:51:57 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../includes/minishell.h"

int is_special_char(char c) 
{
    return c == '<' || c == '>' || c == '|';
}

size_t calculate_size(const char *input) 
{
    size_t extra;
    int i;
    
    extra = 0;
    i = 0;
    while (input[i] != '\0') 
    {
        if (is_special_char(input[i])) 
        {
            if ((input[i] == '<' && input[i+1] == '<') || (input[i] == '>' && input[i+1] == '>')) 
            {
                i++;
                if (i == 1 || input[i-2] != ' ')
                    extra++;
                if (input[i+1] != ' ')
                    extra++;
            } 
            else 
            {
                if (i == 0 || input[i-1] != ' ') 
                    extra++;
                if (input[i+1] != ' ') 
                    extra++;
            }
        }
        i++;
    }
    return (strlen(input) + extra + 1);
}

void handle_special_char(const char *input, char *output, int *i, int *j) 
{
    int aspas;

    aspas =  0;
    if ((input[*i] == '<' && input[*i + 1] == '<') || (input[*i] == '>' && input[*i + 1] == '>')) 
    {
        if (*j > 0 && output[*j - 1] != ' ')
            output[(*j)++] = ' ';
        output[(*j)++] = input[(*i)++];
        output[(*j)++] = input[*i];
        if (input[*i + 1] != ' ' && input[*i + 1] != '\0')
            output[(*j)++] = ' ';
    } 
    else if (is_special_char(input[*i]))
    {
        if (*j > 0 && output[*j - 1] != ' ')
            output[(*j)++] = ' ';
        output[(*j)++] = input[*i];
        if (input[*i + 1] != ' ' && input[*i + 1] != '\0')
            output[(*j)++] = ' ';
    } 
    else
        output[(*j)++] = input[*i];
}

char* add_spaces(const char *input) 
{
    size_t required_size = calculate_size(input);
    char *output = (char*)malloc(required_size * sizeof(char));
    if (output == NULL) return NULL;

    int i = 0;
    int j = 0;
    while (input[i] != '\0') {
        handle_special_char(input, output, &i, &j);
        i++;
    }
    output[j] = '\0';
    return output;
}

// int main() 
// {
//     const char *input = "a<b|    c>>d <<e>f";
//     char *output = add_spaces(input);
//     printf("Output: %s\n", output);
//     free(output);
//     return 0;
// }


/////////////////////////////////////////// ver com johny se esta parte esta bem / faz sentido ///////////////////////////////////////////////

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

char *substr(const char *str, int start, int len) 
{
    char *sub;

    sub = (char *)malloc(len + 1);
    if (!sub)
        return (NULL);
    strncpy(sub, str + start, len);
    sub[len] = '\0';
    return (sub);
}

char **split_by_spaces(const char *input) // 29 lines !!!
{
    int word_count;
    char **matrix;
    int i;
    int k;
    int start;

    if (!input) 
        return NULL;
    word_count = count_words2(input);
    matrix = (char **)malloc((word_count + 1) * sizeof(char *));
    if (!matrix)
        return NULL;
    i = 0;
    k = 0;
    start = 0;
    while (input[i]) 
    {
        if (!ft_isspace(input[i])) 
        {
            start = i;
            while (input[i] && !ft_isspace(input[i])) 
                i++;
            matrix[k++] = substr(input, start, i - start);
        } 
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

    
//     test_input = "This is a test string for split_by_spaces.";
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

char *func(char *str)
{
    int aspas;
    int i = 0;

    i = 0;
    aspas = 0;
    while(str && str[i] != '\0')
    {
        if(str[i] == '"')
        {
            aspas = 1;
            while(str && str[i] != '\0' && str[i] != '"')
                i++;
        }
        aspas = 0;
        i++;
    }
}