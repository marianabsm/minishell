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

#include "../includes/minishell.h"

void double_quoted_string(const char *input, char *output, int *i, int *j) 
{
    output[(*j)++] = input[(*i)++];
    while (input[*i] != '\0' && input[*i] != '"')
        output[(*j)++] = input[(*i)++];
    if (input[*i] == '"')
        output[(*j)++] = input[(*i)++];
}

void single_quoted_string(const char *input, char *output, int *i, int *j) 
{
    output[(*j)++] = input[(*i)++];
    while (input[*i] != '\0' && input[*i] != '\'')
        output[(*j)++] = input[(*i)++];
    if (input[*i] == '\'')
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

size_t calculate_size(const char *input) // 28 lines
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
    return (ft_strlen(input) + extra + 1);
}
int check_open_single_quotes(const char *str)
{
    int i;
    int single_quote_open;
    
    single_quote_open = 0;
    i = 0;
    if(!str)
        return(0);
    while (str && str[i] != '\0')
    {
        if (str[i] == '\'')
            single_quote_open = !single_quote_open;
        i++;
    }
    return (single_quote_open == 0);
}

int check_open_double_quotes(const char *str)
{
    int i;
    int double_quote_open;
    
    double_quote_open= 0;
    i = 0;
    if(!str)
        return(0);
    while (str && str[i] != '\0')
    {
        if (str[i] == '"')
            double_quote_open = !double_quote_open;
        i++;
    }
    return (double_quote_open == 0);
}

char *add_spaces(const char *input)
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
            double_quoted_string(input, output, &i, &j);
        else if (input[i] == '\'') 
            single_quoted_string(input, output, &i, &j);
        else if (is_special_char(input[i]))
            handle_special_char(input, output, &i, &j);
        else
            output[j++] = input[i++];
    }
    output[j] = '\0';
    if(check_open_single_quotes(output) && check_open_double_quotes(output))
        return(output);
    free(output);
    return (NULL);
}
        
    

// int main() 
// {
//     const char *input = "a<b| 'bligghg<<blo blu hh'    \"c>>d\" <<e>f";
//     char *output = add_spaces(input);
//     printf("Output: %s\n", output);
//     free(output);
//     return 0;
// }
