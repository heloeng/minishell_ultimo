/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05.2-lexer_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dydaniel <dydaniel@student.42sp.org.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:46:15 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/15 21:20:35 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Adds a new token to the end of the token list.
 *   - If the list is empty, sets the new token as the head
 *   - Otherwise, traverses to the end and appends the new token
 */
void	append_token_to_list(t_token **list, t_token *new)
{
	t_token	*tmp;

	if (!*list)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

/*
 * Creates and initializes a new token.
 *   - Allocates memory for the token
 *   - Sets its value, type, and quote_type
 *   - Initializes next to NULL
 *   - Returns a pointer to the new token, or NULL on allocation failure
 */
t_token	*new_token(char *value, t_token_type type, char quote_type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->quote_type = quote_type;
	token->next = NULL;
	return (token);
}

/*
 * Frees a linked list of tokens.
 *   - Frees the string value of each token (if present)
 *   - Frees each token node
 */
void	free_token_list(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}
