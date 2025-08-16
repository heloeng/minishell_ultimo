/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07.2-expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dydaniel <dydaniel@student.42sp.org.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 20:49:13 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/15 21:23:40 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_dollar(t_expander_context *ctx);

/*
 * Appends all characters inside single quotes to the result string.
 *   - Skips the opening and closing quote
 *   - Does not expand variables inside single quotes
 */
static void	process_single_quotes(const char *input, int *i, char **res)
{
	char	tmp[2];

	(*i)++;
	while (input[*i] && input[*i] != '\'')
	{
		tmp[0] = input[*i];
		tmp[1] = '\0';
		append_str(res, tmp);
		(*i)++;
	}
	if (input[*i] == '\'')
		(*i)++;
}

/*
 * Processes all characters inside double quotes.
 *   - Expands variables with '$'
 *   - Appends other characters literally
 */
static void	process_double_quotes(t_expander_context *ctx)
{
	char	tmp[2];

	(*(ctx->i))++;
	while (ctx->input[*(ctx->i)] && ctx->input[*(ctx->i)] != '\"')
	{
		if (ctx->input[*(ctx->i)] == '$')
			handle_dollar(ctx);
		else
		{
			tmp[0] = ctx->input[*(ctx->i)];
			tmp[1] = '\0';
			append_str(ctx->res, tmp);
			(*(ctx->i))++;
		}
	}
	if (ctx->input[*(ctx->i)] == '\"')
		(*(ctx->i))++;
}

/*
 * Expands a variable name after a '$' character.
 *   - Extracts the variable name from input
 *   - Appends its value from the environment or exit status
 *   - If no name is found, appends the literal '$'
 */
static void	handle_dollar(t_expander_context *ctx)
{
	char	*name;
	char	*value;
	char	*tmp;

	(*(ctx->i))++;
	name = extract_var_name(ctx->input, ctx->i);
	if (!name)
	{
		append_str(ctx->res, "$");
		return ;
	}
	if (ft_strcmp(name, "?") == 0)
		value = ft_itoa(ctx->last_exit_status);
	else
	{
		tmp = get_env_var(ctx->env, name);
		if (tmp)
			value = ft_strdup(tmp);
		else
			value = ft_strdup("");
	}
	append_str(ctx->res, value);
	free(name);
	free(value);
}

/*
 * Appends a single character to the result string.
 */
static void	append_char(char **res, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	append_str(res, tmp);
}

/*
 * Handles one segment of the input string:
 *   - Processes single-quoted strings literally
 *   - Processes double-quoted strings with expansion
 *   - Expands variables starting with '$'
 *   - Appends any other character
 */
void	handle_expansion(t_expander_context *ctx)
{
	if (ctx->input[*(ctx->i)] == '\'')
		process_single_quotes(ctx->input, ctx->i, ctx->res);
	else if (ctx->input[*(ctx->i)] == '\"')
		process_double_quotes(ctx);
	else if (ctx->input[*(ctx->i)] == '$')
		handle_dollar(ctx);
	else
	{
		append_char(ctx->res, ctx->input[*(ctx->i)]);
		(*(ctx->i))++;
	}
}
