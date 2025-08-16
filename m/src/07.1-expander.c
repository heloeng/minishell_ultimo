/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07.1-expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dydaniel <dydaniel@student.42sp.org.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 10:12:59 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/15 21:22:59 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Expands all variables in the given input string using environment variables.
 *   - Creates a new string with expansions resolved
 *   - Uses a context struct to pass input, output and state
 *   - Calls handle_expansion to process each segment
 * Returns:
 *   Newly allocated expanded string, or NULL on allocation failure
 */
static char	*expand_string(const char *input, t_env *env, int last_exit_status)
{
	char				*res;
	int					i;
	t_expander_context	ctx;

	res = ft_strdup("");
	if (!res)
		return (NULL);
	i = 0;
	while (input[i])
	{
		ctx.input = input;
		ctx.i = &i;
		ctx.res = &res;
		ctx.env = env;
		ctx.last_exit_status = last_exit_status;
		handle_expansion(&ctx);
	}
	return (res);
}

/*
 * Checks if a string starts with a quote character.
 *   - Returns 1 if the first character is a single or double quote
 *   - Returns 0 otherwise or if the string is NULL
 */
static int	is_quoted(const char *s)
{
	if (!s)
		return (0);
	return (s[0] == '\'' || s[0] == '"');
}

/*
 * Expands variables in each argument of the command.
 *   - Allocates a new argv array for the expanded arguments
 *   - Expands each argument using the environment and last exit status
 *   - Skips and frees arguments that become empty (unless quoted)
 *   - Frees the original argv and replaces it with the new one
 *   - Uses only 5 variables and avoids for/ternary operators
 */
static void	expand_argvs(t_command *cmd, t_env *env, int status)
{
	int		i;
	int		j;
	char	**new_argv;
	char	*expanded;
	int		count;

	i = 0;
	j = 0;
	count = count_args(cmd->argv);
	new_argv = malloc(sizeof(char *) * (count + 1));
	if (!new_argv)
		return ;
	while (i < count)
	{
		expanded = expand_string(cmd->argv[i], env, status);
		if (expanded[0] != '\0' || is_quoted(cmd->argv[i]))
			new_argv[j++] = expanded;
		else
			free(expanded);
		free(cmd->argv[i]);
		i++;
	}
	new_argv[j] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
}

/*
 * Expands all filenames in the redirections of the current command.
 *   - Replaces each redirection's file string with its expanded version
 */
static void	expand_redirects(t_command *current_cmd, t_env *env,
	int last_exit_status)
{
	t_redirect	*redir;
	char		*expanded;

	redir = current_cmd->redirects;
	while (redir)
	{
		expanded = expand_string(redir->file, env, last_exit_status);
		free(redir->file);
		redir->file = expanded;
		redir = redir->next;
	}
}

/*
 * Expands all argv and redirect fields for all commands in the pipeline.
 *   - Traverses each command
 *   - Expands arguments and redirection filenames
 */
void	expand_all(t_command *cmd_head, t_env *env, int last_exit_status)
{
	t_command	*current_cmd;

	current_cmd = cmd_head;
	while (current_cmd)
	{
		expand_argvs(current_cmd, env, last_exit_status);
		expand_redirects(current_cmd, env, last_exit_status);
		current_cmd = current_cmd->next;
	}
}
