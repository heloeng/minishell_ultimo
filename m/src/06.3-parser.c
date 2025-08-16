/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06.3-parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dydaniel <dydaniel@student.42sp.org.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:16:16 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/15 21:22:20 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Adds a new argument to the argv array of the given command.
 *   - Allocates a new argv array with space for the new argument
 *   - Copies existing arguments to the new array
 *   - Adds the new argument at the end
 *   - Frees the old argv array
 */
static void	add_argv(t_command *current_cmd, char *value)
{
	int		argc;
	int		i;
	char	**new_argv;

	if (!current_cmd || !value)
		return ;
	argc = 0;
	if (current_cmd->argv)
		while (current_cmd->argv[argc])
			argc++;
	new_argv = ft_calloc(argc + 2, sizeof(char *));
	if (!new_argv)
		return ;
	i = 0;
	while (i < argc)
	{
		new_argv[i] = current_cmd->argv[i];
		i++;
	}
	new_argv[i] = ft_strdup(value);
	new_argv[i + 1] = NULL;
	free(current_cmd->argv);
	current_cmd->argv = new_argv;
}

/*
 * Adds a new redirection to the given command's redirection list.
 *   - Allocates a new redirection node
 *   - Sets its type and file target
 *   - Appends it to the end of the current redirection list
 */
static void	add_redirect(t_command *current_cmd, t_token_type type,
	char *file)
{
	t_redirect	*new;
	t_redirect	*last;

	if (!current_cmd || !file)
		return ;
	new = malloc(sizeof(t_redirect));
	if (!new)
		return ;
	new->type = type;
	new->file = ft_strdup(file);
	new->next = NULL;
	if (!current_cmd->redirects)
	{
		current_cmd->redirects = new;
		return ;
	}
	last = current_cmd->redirects;
	while (last->next)
		last = last->next;
	last->next = new;
}

/*
 * Handles redirection tokens and adds them to the current command.
 *   - Validates that the redirection has a following argument
 *   - Adds the redirection with the corresponding type and file
 *   - Frees all commands and aborts on syntax error
 * Returns:
 *   1 if successful, 0 if there was a syntax error
 */
static int	handle_redirection(t_command *current_cmd,
	t_token *token, t_command *cmd_head)
{
	t_token	*next;

	next = token->next;
	if (!next || next->type != T_WORD)
	{
		printf("Syntax error: missing filename after redirection\n");
		free_cmds(cmd_head);
		return (0);
	}
	if (token->type == T_REDIR_IN)
		add_redirect(current_cmd, T_REDIR_IN, next->value);
	else if (token->type == T_HEREDOC)
		add_redirect(current_cmd, T_HEREDOC, next->value);
	else if (token->type == T_REDIR_OUT)
		add_redirect(current_cmd, T_REDIR_OUT, next->value);
	else if (token->type == T_APPEND)
		add_redirect(current_cmd, T_APPEND, next->value);
	return (1);
}

/*
 * Adds a token to the current command.
 *   - If token is a WORD, adds it to argv
 *   - If token is a redirection, processes and adds it
 *   - If token is a pipe, signals a new command should start
 *   - Advances token pointer accordingly
 */
void	add_token_to_cmd(t_token **token, t_command **current_cmd,
	t_command **cmd_head)
{
	if ((*token)->type == T_WORD)
		add_argv(*current_cmd, (*token)->value);
	else if ((*token)->type == T_REDIR_IN || (*token)->type == T_HEREDOC
		|| (*token)->type == T_REDIR_OUT || (*token)->type == T_APPEND)
	{
		if (!handle_redirection(*current_cmd, *token, *cmd_head))
		{
			*token = NULL;
			return ;
		}
		*token = (*token)->next;
	}
	else if ((*token)->type == T_PIPE)
		*current_cmd = NULL;
}
