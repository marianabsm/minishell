/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:28:30 by marianamest       #+#    #+#             */
/*   Updated: 2025/05/20 14:17:36 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char * ft_strtrim (char *s, char c)
{
    int i;
    int j;
    char *result;

    if (!s)
        return (NULL);
    i = 0;
    j = ft_strlen(s) - 1;
    while (s[i] && s[i] == c)
        i++;
    while (j > i && s[j] == c)
        j--;
    result = malloc(sizeof(char) * (j - i + 2));
    if (!result)
        return (NULL);
    ft_strlcpy(result, &s[i], j - i + 2);
    free(s);
    return (result);
}
