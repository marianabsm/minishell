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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_special_char(char c) 
{
    return (c == '<' || c == '>' || c == '|');
}
void handle_quoted_string(const char *input, char *output, int *i, int *j) 
{
    output[(*j)++] = input[(*i)++];
    while (input[*i] != '\0' && input[*i] != '"')
        output[(*j)++] = input[(*i)++];
    if (input[*i] == '"')
        output[(*j)++] = input[(*i)++];
}

void handle_special_char(const char *input, char *output, int *i, int *j) 
{
    if (*j > 0 && output[*j - 1] != ' ')
        output[(*j)++] = ' ';
    output[(*j)++] = input[(*i)++];
    if ((input[*i - 1] == '<' && input[*i] == '<') || (input[*i - 1] == '>' && input[*i] == '>'))
        output[(*j)++] = input[(*i)++];
    if (input[*i] != ' ' && input[*i] != '\0') 
        output[(*j)++] = ' ';
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
            if ((input[i] == '<' && input[i + 1] == '<') || (input[i] == '>' && input[i + 1] == '>')) 
            {
                i++;
                if (i == 1 || input[i - 2] != ' ')
                    extra++;
                if (input[i + 1] != ' ')
                    extra++;
            } 
            else 
            {
                if (i == 0 || input[i - 1] != ' ') 
                    extra++;
                if (input[i + 1] != ' ') 
                    extra++;
            }
        }
        i++;
    }
    return (strlen(input) + extra + 1);
}

char* add_spaces(const char *input) 
{
    char *output;
    int i;
    int j;
    
    i = 0;
    j = 0;
    output = (char*)malloc(calculate_size(input) * sizeof(char));
    if (output == NULL) 
        return (NULL);

    while (input[i] != '\0') 
    {
        if (input[i] == '"') 
            handle_quoted_string(input, output, &i, &j);
        else if (is_special_char(input[i]))
            handle_special_char(input, output, &i, &j);
        else
            output[j++] = input[i++];
    }
    output[j] = '\0';
    return (output);
}



// int main() 
// {
//     const char *input = "a<b|    \"c>>d\" <<e>f";
//     char *output = add_spaces(input);
//     printf("Output: %s\n", output);
//     free(output);
//     return 0;
// }

/////////////////////////////////////////// segunda parte ///////////////////////////////////////////

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

static char *extract_next_token(const char *input, int *i) 
{
    int start;
    char *token;

    if (input[*i] == '"') 
    {
        start = ++(*i);
        while (input[*i] && input[*i] != '"') 
            (*i)++;
        token = substr(input, start, *i - start);
        if (input[*i] == '"') 
            (*i)++;
        return (token);
    }
    start = *i;
    while (input[*i] && !ft_isspace2(input[*i]) && input[*i] != '"') 
        (*i)++;
    return (substr(input, start, *i - start));
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

int main(void)
{
    const char *test_input;
    char **result;
    int i;

    
    test_input = "This is a \"test string\" for split_by_spaces.";
    result = split_by_spaces(test_input);
    if (!result) 
    {
        printf("Error: split_by_spaces returned NULL.\n");
        return (1);
    }
    printf("Words in the input string:\n");
    for (i = 0; result[i] != NULL; i++) 
    {
        printf("Word %d: %s\n", i + 1, result[i]);
        free(result[i]);
    }
    free(result);
    return (0);
}

