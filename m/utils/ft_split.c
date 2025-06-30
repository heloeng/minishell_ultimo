/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dydaniel <dydaniel@student.42sp.org.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:39:49 by dydaniel          #+#    #+#             */
/*   Updated: 2024/10/22 13:59:28 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>

size_t	ft_lenword(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	return (i);
}

char	*ft_get_str(char const *s, int len)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_move_w(char **list, char const *s, char c)
{
	char	**list_words;
	int		len_word;

	list_words = (char **)list;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s == '\0')
			break ;
		len_word = ft_lenword(s, c);
		*list_words++ = ft_get_str(s, len_word);
		if (list_words == NULL)
			return (NULL);
		s += len_word;
	}
	*list_words = NULL;
	return (list);
}

size_t	ft_count_words(const char *s, char c)
{
	int	words;

	words = 0;
	while (*s)
	{
		while (*s == c && *s != '\0')
			s++;
		if (*s != c && *s != '\0')
			words++;
		while (*s != c && *s != '\0')
			s++;
	}
	return (words);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	words;

	words = ft_count_words(s, c);
	split = malloc(sizeof(char *) * (words + 1));
	if (split == NULL)
		return (NULL);
	return (ft_move_w(split, s, c));
}
