/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dydaniel <dydaniel@student.42sp.org.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:35:31 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/05 22:48:50 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_valid_char(char c, int base)
{
	char	digits_low[17];
	char	digits_up[17];

	ft_strlcpy(digits_low, "0123456789abcdef", 17);
	ft_strlcpy(digits_up, "0123456789ABCDEF", 17);
	while (base--)
	{
		if (digits_low[base] == c || digits_up[base] == c)
			return (1);
	}
	return (0);
}

int	ft_char_value(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (0);
}

long	ft_atoi_base(const char *nptr, int base)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*nptr == '\r' || *nptr == '\t' || *nptr == '\f' || \
				*nptr == '\n' || *nptr == ' ' || *nptr == '\v')
			nptr++;
	if (*nptr == '-')
		sign = sign * (-1);
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (ft_valid_char(*nptr, base))
	{
		result = result * base + ft_char_value(*nptr);
		nptr++;
	}
	return (result * sign);
}
