/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianamestre <marianamestre@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:14:13 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 14:14:14 by marianamest      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;

	str = s;
	while (n--)
	{
		*str = c;
		str++;
	}
	return (s);
}

void	*safe_malloc(size_t size)
{
	void	*new;

	new = NULL;
	new = (void *)malloc(size);
	if (!new)
	{
		ft_putstr_fd("Failed malloc\n", STDERR_FILENO);
		free_and_exit(msh());
		exit(1);
	}
	ft_memset(new, '\0', size);
	return (new);
}

void	ft_skip_whitespace(const char **s)
{
	while (**s == ' ' || **s == '\t' || **s == '\n' || **s == '\v'
		|| **s == '\f' || **s == '\r')
		(*s)++;
}

int	ft_parse_sign(const char **s)
{
	int	sign;

	sign = 1;
	if (**s == '-' || **s == '+')
	{
		if (**s == '-')
			sign = -1;
		(*s)++;
	}
	return (sign);
}

int	ft_detect_base(const char **s, int base)
{
	if ((base == 0 || base == 16) && (*s)[0] == '0' && ((*s)[1] == 'x'
			|| (*s)[1] == 'X'))
	{
		*s += 2;
		return (16);
	}
	else if (base == 0 && **s == '0')
	{
		(*s)++;
		return (8);
	}
	else if (base == 0)
		return (10);
	return (base);
}
