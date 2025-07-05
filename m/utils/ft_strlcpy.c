/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dydaniel <dydaniel@student.42sp.org.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:02:11 by dydaniel          #+#    #+#             */
/*   Updated: 2024/10/16 14:52:51 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "minishell.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	s;

	s = 0;
	i = 0;
	while (src[s])
		s++;
	if (size == 0)
		return (s);
	while (i < s && (size - 1) > 0)
	{
		dest[i] = src[i];
		i++;
		size--;
	}
	dest[i] = '\0';
	return (s);
}

size_t ft_strcpy_quote(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	s;
	size_t	j;
	char c;

	s = 0;
	i = 0;
	j = 0;
	while (src[s])
		s++;
	if (size == 0)
		return (s);
	c = src[i];
	while (i + 1 < s && (size - 1) > 0)
	{
		if ((src[i] == '"' || src[i] == '\'') && (src[i + 1] == '"' || src[i + 1] == '\''))
			i += 2;
		dest[j] = src[i];
		i++;
		j++;
		size--;
	}
	dest[j] = c;
	dest[j + 1] = '\0';
	return (s);
}