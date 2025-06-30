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
