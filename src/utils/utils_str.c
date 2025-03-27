/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-c <msilva-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:50:45 by msilva-c          #+#    #+#             */
/*   Updated: 2025/03/22 13:14:05 by msilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* returns 0 if it's equal, non-zero if not */
int	ft_strcmp(const char *s1, const char *s2)
{
	char	*s01;
	char	*s02;

	if (!s1 && !s2)
		return (0); // Both strings are NULL, considered equal
	s01 = (char *)s1;
	s02 = (char *)s2;
	while (*s01 && *s02)
	{
		if (*s01 != *s02)
			return (*s01 - *s02);
		s01++;
		s02++;
	}
	return (*s01 - *s02);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	n;
	unsigned int	i;

	if (!s)
		return (NULL);
	n = ft_strlen((char *)s);
	if (start >= n || len == 0)
		return (ft_strdup(""));
	if (len > n - start)
		len = n - start;
	sub = (char *)safe_malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len && s[i + start])
	{
		sub[i] = s[i + start];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*ft_strdup(const char *s)
{
	char	*copy;
	size_t	n;
	size_t	i;

	i = 0;
	if (!s)
		return NULL;
	n = ft_strlen((char *)s);
	copy = (char *)safe_malloc(sizeof(char) * (n + 1));
	if (!copy)
		return (NULL);
	while (s[i])
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
