/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06.1-parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dydaniel <dydaniel@student.42sp.org.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 10:14:17 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/05 22:10:27 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Checks for syntax errors in the token list.
 * Returns:
 *   1 - if a syntax error is found
 *   0 - if the syntax is valid
 * Errors handled:
 *   - Empty input
 *   - Pipe at the beginning
 *   - Two consecutive pipes
 *   - Redirections without following argument
 */
int	check_syntax_errors(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	if (!curr)
		return (printf("Error: empty command\n"), 1);
	if (curr->type == T_PIPE)
		return (printf("Syntax error: pipe at the beginning\n"), 1);
	while (curr)
	{
		if (curr->type == T_PIPE)
		{
			if (!curr->next || curr->next->type == T_PIPE)
				return (printf("Syntax error: misplaced pipe\n"), 1);
		}
		else if (curr->type == T_REDIR_IN || curr->type == T_REDIR_OUT
			|| curr->type == T_HEREDOC || curr->type == T_APPEND)
		{
			if (!curr->next || curr->next->type != T_WORD)
				return (printf("Error: redirection without argument\n"), 1);
		}
		curr = curr->next;
	}
	return (0);
}

/*
 * Checks whether a command is a builtin.
 * Returns:
 *   1 - if the command matches a known builtin
 *   0 - otherwise
 */
int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

/*
 * Parses the token list into a linked list of command structures.
 *   - Initializes a new command when needed
 *   - Adds tokens to the current command
 * Returns:
 *   - The head of the command list
 *   - NULL if allocation fails
 */
t_command	*parser(t_token *tokens)
{
	t_command	*cmd_head;
	t_command	*current_cmd;
	t_token		*token;

	cmd_head = NULL;
	current_cmd = NULL;
	token = tokens;
	while (token)
	{
		if (!current_cmd)
		{
			current_cmd = init_command(&cmd_head);
			if (!current_cmd)
				return (NULL);
		}
		add_token_to_cmd(&token, &current_cmd, &cmd_head);
		if (token)
			token = token->next;
	}
	return (cmd_head);
}
