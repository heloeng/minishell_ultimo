/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dydaniel <dydaniel@student.42sp.org.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:11:57 by dydaniel          #+#    #+#             */
/*   Updated: 2024/10/21 11:57:35 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "minishell.h"

int	ft_lenstr(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_charinset(char const s, char *set)
{
	while (*set)
	{
		if (*set == s)
			return (1);
		set++;
	}
	return (0);
}

void	*ft_cpynmem(char *dest, const char *src, int n)
{
	int		i;
	char	*cpy;

	i = 0;
	cpy = dest;
	while (n > 0)
	{
		cpy[i] = src[i];
		i++;
		n--;
	}
	cpy[i] = '\0';
	return (dest);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	int		len_s1;
	int		i;

	len_s1 = ft_lenstr(s1);
	i = 0;
	while (ft_charinset((char const)s1[len_s1 - 1], (char *)set))
		len_s1 -= 1;
	while (ft_charinset((char const)s1[i], (char *)set) && len_s1 > 0)
		i++;
	len_s1 -= i;
	s1 += i;
	i = 0;
	trimmed = malloc(len_s1 + 1);
	if (trimmed == NULL)
		return (NULL);
	while (i < len_s1)
	{
		trimmed[i] = s1[i];
		i++;
	}
	trimmed[i] = '\0';
	return (trimmed);
}
