/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:45:21 by helde-so          #+#    #+#             */
/*   Updated: 2025/08/05 22:55:41 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_unclosed_quote(char *str)
{
	char	quote;

	quote = '\0';
	while (*str)
	{
		if (*str == '\'' || *str == '"')
		{
			if (!quote)
				quote = *str;
			else if (quote == *str)
				quote = '\0';
		}
		str++;
	}
	return (quote != '\0');
}

char	*complete_unclosed_quote(char *text)
{
	char	*temp;
	char	*joined;

	while (has_unclosed_quote(text))
	{
		temp = readline("> ");
		if (!temp)
			break ;
		joined = ft_strjoin(text, "\n");
		free(text);
		text = ft_strjoin(joined, temp);
		free(joined);
		free(temp);
	}
	return (text);
}

int	char_inside_quotes(const char *str, int index)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (i < index && str[i])
	{
		if (str[i] == '\'' && !double_quote)
		{
			single_quote = !single_quote;
		}
		else if (str[i] == '"' && !single_quote)
		{
			double_quote = !single_quote;
		}
		i++;
	}
	return (single_quote || double_quote);
}
