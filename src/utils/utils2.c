/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:14:04 by marianamest       #+#    #+#             */
/*   Updated: 2025/06/10 17:40:53 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static const char	*skip_and_parse(const char *str, int *sign, int *base)
{
	const char	*s = str;

	ft_skip_whitespace(&s);
	*sign = ft_parse_sign(&s);
	*base = ft_detect_base(&s, *base);
	return (s);
}

static int	handle_digit(long long *result, int digit, int base, int sign)
{
	if (*result > (LLONG_MAX - digit) / base)
	{
		ft_handle_overflow(sign, result);
		return (0);
	}
	*result = *result * base + digit;
	return (1);
}

static const char	*parse_digits(const char *s, int base, int sign,
		long long *result)
{
	int	digit;

	while (ft_isdigit_base(*s, base))
	{
		digit = ft_getdigit(*s);
		if (digit < 0 || digit >= base)
			break ;
		if (!handle_digit(result, digit, base, sign))
		{
			msh()->any = 1;
			s++;
			while (ft_isdigit_base(*s, base))
				s++;
			break ;
		}
		msh()->any = 1;
		s++;
	}
	return (s);
}

long long	ft_strtoll(const char *str, char **endptr, int base)
{
	const char	*s;
	long long	result;
	int			sign;

	result = 0;
	msh()->any = 0;
	s = skip_and_parse(str, &sign, &base);
	errno = 0;
	s = parse_digits(s, base, sign, &result);
	if (endptr != NULL)
	{
		if (msh()->any)
			*endptr = (char *)s;
		else
			*endptr = (char *)str;
	}
	if (sign == -1 && result != LLONG_MIN && result != LLONG_MAX)
		result = -result;
	return (result);
}

char	*strip_outer_quotes(const char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len >= 2 && ((str[0] == '\'' && str[len - 1] == '\'') || (str[0] == '"'
				&& str[len - 1] == '"')))
		return (ft_substr(str, 1, len - 2));
	return (ft_strdup(str));
}
