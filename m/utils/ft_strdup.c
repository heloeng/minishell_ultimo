/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dydaniel <dydaniel@student.42sp.org.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:45:39 by dydaniel          #+#    #+#             */
/*   Updated: 2024/10/30 14:26:40 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include<stddef.h>
#include "../minishell.h"

void	*ft_memcpy_str(void *dest, const char *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;
	size_t				i;

	i = 0;
	s = (const unsigned char *)src;
	d = (unsigned char *)dest;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*copy;

	size = 0;
	while (s[size] != '\0')
		size++;
	copy = malloc(size + 1);
	if (copy == NULL)
		return (NULL);
	ft_memcpy_str(copy, s, size);
	return ((char *)copy);
}
