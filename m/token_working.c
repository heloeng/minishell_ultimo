/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_working.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dydaniel <dydaniel@student.42sp.org.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:05:47 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/05 21:53:43 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		while (text[++i] && !ft_isspace(text[i]))
		{
			if (text[i] == '"' || text[i] == '\'')
			{
				quote = text[i];
				i++;
				val = 1;
				break ;
			}
			size++;
		}
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
	while (*text)
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

int	size_of_token(char *text)
{
	if (*text == '\'' || *text == '"')
		return (size_of_quote(text));
	else if (is_operator(text))
		return (is_operator(text));
	else
		return (size_of_string(text));
}

void	token_n_copy(char *token_i, int size, char **text)
{
	int		k;
	char	c;

	k = 0;
	while (k < size)
	{
		if (**text == '\'' || **text == '"')
		{
			c = **text;
			(*text)++;
			while (**text != c)
			{
				if (**text == '\\' && (*(*text + 1) == '\'' || \
							//*(*text) + 1 == '"'))
							*(*text + 1) == '"'))//ALTEREI AQUI
					(*text)++;
				token_i[k] = (**text);
				k++;
				(*text)++;
			}
			(*text)++;
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
	//print_tokens(*token);
}

void	free_tokens(char ***token)
{
	int	i;

	i = 0;
	while ((*token)[i])
	{
		free((*token)[i]);
		i++;
	}
	free(*token);
	(*token) = NULL;
}
