/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07.3-expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:34:55 by helde-so          #+#    #+#             */
/*   Updated: 2025/08/15 21:24:21 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Extracts a variable name from a braced expression like `${VAR}`.
 *   - Assumes the current character is '{'
 *   - Advances past the '{' and collects alphanumeric or '_' characters
 *   - Stops at the closing '}'
 *   - Returns a newly allocated string with the variable name
 *   - Returns NULL if closing '}' is not found or name is empty
 *   - Advances the index past the closing '}'
 */
static char	*extract_braced_var(const char *input, int *i)
{
	int		start;
	char	*name;

	(*i)++;
	start = *i;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
		(*i)++;
	if (input[*i] != '}')
		return (NULL);
	name = ft_strndup(input + start, *i - start);
	(*i)++;
	return (name);
}

/*
 * Extracts a variable name after a '$' symbol.
 *   - Supports four forms: $? (exit status), ${VAR}, $VAR, and $<digit>
 *   - If the next character is '?', returns "?" as a special case
 *   - If the next character is a digit, treats it as a positional parameter
 *   - If the next character is '{', delegates to extract_braced_var()
 *     and returns an empty string (unsupported in this shell)
 *   - Otherwise collects alphanumeric or '_' characters as the name
 *   - Returns a newly allocated string with the variable name
 *   - Returns NULL if no valid name is found
 *   - Advances the index to the character after the variable name
 */
char	*extract_var_name(const char *input, int *i)
{
	int		start;
	char	*name;

	if (input[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	if (ft_isdigit(input[*i]))
	{
		(*i)++;
		return (ft_strdup(""));
	}
	if (input[*i] == '{')
		return (extract_braced_var(input, i));
	start = *i;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
		(*i)++;
	if (*i == start)
		return (NULL);
	name = ft_strndup(input + start, *i - start);
	return (name);
}

/*
 * Appends the source string to the destination string.
 *   - Allocates a new string to hold the result
 *   - Copies the current content of `*dst` if it exists
 *   - Appends the `src` string to the end
 *   - Frees the old `*dst` and updates it with the new one
 *   - Does nothing if `src` is NULL
 */
void	append_str(char **dst, const char *src)
{
	char	*tmp;
	size_t	len_dst;
	size_t	len_src;

	if (!src)
		return ;
	if (*dst)
		len_dst = ft_strlen(*dst);
	else
		len_dst = 0;
	len_src = ft_strlen(src);
	tmp = *dst;
	*dst = malloc(len_dst + len_src + 1);
	if (*dst)
	{
		if (tmp)
			ft_strcpy(*dst, tmp);
		else
			(*dst)[0] = '\0';
		ft_strcat(*dst, src);
	}
	free(tmp);
}

/*
 * Counts the number of non-NULL entries in a NULL-terminated array.
 *   - Iterates through the `argv` array
 *   - Returns the total number of elements before the NULL terminator
 *   - Returns 0 if `argv` itself is NULL
 */
int	count_args(char **argv)
{
	int	count;

	count = 0;
	while (argv && argv[count])
		count++;
	return (count);
}
