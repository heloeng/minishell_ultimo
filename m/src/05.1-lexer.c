/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05.1-lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dydaniel <dydaniel@student.42sp.org.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:05:47 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/15 21:20:25 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Skips over a quoted section of the input.
 *   - Stores the quote type (single or double) in `quote_type`
 *   - Advances `i` past the closing quote
 *   - Returns 1 on success, 0 if quote is not closed
 */
static int	skip_quoted_word(char *input, int *i, char *quote_type)
{
	char	q;

	q = input[*i];
	*quote_type = q;
	(*i)++;
	while (input[*i] && input[*i] != q)
		(*i)++;
	if (input[*i] == '\0')
	{
		printf("minishell error: unclosed %c quote\n", q);
		return (0);
	}
	(*i)++;
	return (1);
}

/*
 * Extracts a word from the input, stopping at a delimiter or special character.
 *   - Handles quoted substrings by calling `skip_quoted_word`
 *   - Returns a newly allocated substring (caller must free)
 *   - Returns NULL if quote is not closed
 */
static char	*extract_word(char *input, int *i, char *quote_type)
{
	int		start;

	*quote_type = 0;
	start = *i;
	while (input[*i] && input[*i] != ' ' && input[*i] != '|'
		&& input[*i] != '<' && input[*i] != '>')
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			if (!skip_quoted_word(input, i, quote_type))
				return (NULL);
		}
		else
			(*i)++;
	}
	return (ft_substr(input, start, *i - start));
}

/*
 * Handles special tokens: pipes and redirection operators.
 *   - Advances `i` past the token
 *   - Adds the token to the list
 *   - Returns 1 if a special token was found, 0 otherwise
 */
static int	handle_special_tokens(char *input, int *i, t_token **tokens)
{
	if (input[*i] == '|' && ++(*i))
		append_token_to_list(tokens, new_token(ft_strdup("|"), T_PIPE, 0));
	else if (input[*i] == '<' && input[*i + 1] == '<')
	{
		*i += 2;
		append_token_to_list(tokens, new_token(ft_strdup("<<"), T_HEREDOC, 0));
	}
	else if (input[*i] == '>' && input[*i + 1] == '>')
	{
		*i += 2;
		append_token_to_list(tokens, new_token(ft_strdup(">>"), T_APPEND, 0));
	}
	else if (input[*i] == '>' && ++(*i))
		append_token_to_list(tokens, new_token(ft_strdup(">"), T_REDIR_OUT, 0));
	else if (input[*i] == '<' && ++(*i))
		append_token_to_list(tokens, new_token(ft_strdup("<"), T_REDIR_IN, 0));
	else
		return (0);
	return (1);
}

/*
 * Handles word tokens (non-special, non-whitespace).
 *   - Extracts a word from the input
 *   - Adds it to the token list
 *   - Returns 1 on success, 0 on failure (e.g. unclosed quote)
 */
static int	handle_word_token(char *input, int *i, t_token **tokens)
{
	char	*word;
	char	quote_type;

	word = extract_word(input, i, &quote_type);
	if (!word)
		return (0);
	append_token_to_list(tokens,
		new_token(ft_strdup(word), T_WORD, quote_type));
	free(word);
	return (1);
}

/*
 * Main lexer function.
 *   - Iterates through the input string and splits it into tokens
 *   - Skips whitespace
 *   - Handles special characters and words
 *   - Returns a linked list of tokens, or NULL on syntax error
 */
t_token	*lexer(char *input)
{
	int		i;
	t_token	*tokens;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (!input[i])
			break ;
		if (!handle_special_tokens(input, &i, &tokens))
		{
			if (!handle_word_token(input, &i, &tokens))
			{
				free_token_list(tokens);
				return (NULL);
			}
		}
	}
	return (tokens);
}
