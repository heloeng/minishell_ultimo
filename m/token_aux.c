/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dydaniel <dydaniel@student.42sp.org.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:46:15 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/11 21:54:58 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	size_of_quote_aux(char *text, int *i, int *size, int *val)
{
	char	quote;

	while (text[++(*i)] && !ft_isspace(text[*i]))
	{
		if (text[*i] == '"' || text[*i] == '\'')
		{
			quote = text[*i];
			(void)quote;
			(*i)++;
			*val = 1;
			break ;
		}
		(*size)++;
	}
}

int	size_of_quote(char *text)
{
	int		i;
	int		size;
	int		val;
	char	quote;

	i = 1;
	size = 0;
	quote = text[0];
	val = 1;
	while (val == 1)
	{
		while (text[i] && text[i] != quote)
		{
			if (text[i] == '\\' && (text[i + 1] == '"' || text[i + 1] == '\''))
				i += 1;
			i++;
			size++;
		}
		val = 0;
		size_of_quote_aux(text, &i, &size, &val);
	}
	return (size);
}

int	size_of_string(char *text)
{
	int		size;
	char	quote;

	size = 0;
	while (*text && !ft_isspace(*text))
	{
		if (*text == '"' || *text == '\'')
		{
			quote = *text;
			text++;
			while (*text && *text != quote)
			{
				text++;
				size++;
			}
			if (!*text)
				break ;
			continue ;
		}
		if (is_operator(text))
			break ;
		text++;
		size++;
	}
	return (size);
}

int	is_operator(char *text)
{
	if (!text)
		return (0);
	if (text[0] == '>' && text[1] == '>')
		return (2);
	else if (text[0] == '<' && text[1] == '<')
		return (2);
	else if (text[0] == '>' || text[0] == '<' || text[0] == '|')
		return (1);
	return (0);
}

int	num_tokens(char *text)
{
	int	j;
	int	op_len;

	j = 0;
	while (*text && *text != '\n')
	{
		while (*text && ft_isspace(*text))
			text++;
		if (!*text)
			break ;
		op_len = is_operator(text);
		if (op_len > 0)
		{
			j++;
			text += op_len;
			continue ;
		}
		j++;
		while (*text && !ft_isspace(*text) && !is_operator(text))
			text++;
	}
	return (j);
}
