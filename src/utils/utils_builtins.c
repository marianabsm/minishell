/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:18:43 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/05 15:30:31 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_error(void)
{
	printf("Error: %s\n", strerror(errno));
}

void	my_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

void	my_strcat(char *dest, const char *src)
{
	int	i;
	int	dest_len;

	if (!dest || !src)
		return ;
	i = 0;
	dest_len = ft_strlen(dest);
	while (src[i])
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
}

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
			&& c <= '9'))
		return (1);
	return (0);
}

void	int_to_str(int num, char *str)
{
	int	i;
	int	is_negative;
	int	j;

	i = 0;
	is_negative = 0;
	if (num < 0)
	{
		is_negative = 1;
		num = -num;
	}
	while (num > 0)
	{
		str[i++] = (num % 10) + '0';
		num /= 10;
	}
	if (is_negative)
		str[i++] = '-';
	j = 0;
	while (j < i / 2)
	{
		ft_swap_char(&str[j], &str[i - j - 1]);
		j++;
	}
	str[i] = '\0';
}
