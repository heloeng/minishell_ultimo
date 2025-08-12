/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_working.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dydaniel <dydaniel@student.42sp.org.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:05:47 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/11 21:54:34 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_of_token(char *text)
{
	if (*text == '\'' || *text == '"')
		return (size_of_quote(text));
	else if (is_operator(text))
		return (is_operator(text));
	else
		return (size_of_string(text));
}

void	token_n_copy_aux(char **token_i, char **text, int *k)
{
	char	c;

	c = **text;
	(*text)++;
	while (**text != c)
	{
		if (**text == '\\' && (*(*text + 1) == '\'' || \
					*(*text) + 1 == '"'))
			(*text)++;
		(*token_i)[*k] = (**text);
		(*k)++;
		(*text)++;
	}
	(*text)++;
}

void	token_n_copy(char *token_i, int size, char **text)
{
	int		k;

	k = 0;
	while (k < size)
	{
		if (**text == '\'' || **text == '"')
		{
			token_n_copy_aux(&token_i, text, &k);
		}
		else
		{
			token_i[k] = (**text);
			k++;
			(*text)++;
		}
	}
	token_i[k] = '\0';
}

void	populate_token(char **token, char *text, int n_tokens)
{
	int	size;
	int	i;

	i = 0;
	while (i < n_tokens)
	{
		while (ft_isspace(*text))
			text++;
		if (!*text)
			break ;
		size = size_of_token(text);
		token[i] = malloc(sizeof(char) * (size + 1));
		if (!token[i])
			return ;
		token_n_copy(token[i], size, &text);
		i++;
	}
	token[i] = NULL;
}

void	divide_arguments(char ***token, char *text)
{
	int	n_tokens;

	n_tokens = num_tokens(text);
	*token = malloc(sizeof(char *) * (n_tokens + 1));
	if (!(*token))
		return ;
	populate_token(*token, text, n_tokens);
}
