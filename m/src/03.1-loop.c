/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03.1-loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:58:11 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/15 21:17:31 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Validates all parsed commands:
 * - If no command is present, shows an error.
 * - For each command, checks if it's valid or reports it as invalid.
 * - Updates shell's exit status accordingly.
 * Returns 1 if all commands are valid or handled, 0 otherwise.
 */
static int	validate_all_commands(t_shell *shell, t_command *cmds)
{
	t_command	*curr;

	if (!cmds)
	{
		write(2, "Error: No command.\n", 20);
		if (shell)
			shell->last_exit_status = 1;
		return (0);
	}
	curr = cmds;
	while (curr)
	{
		if (!is_command_valid(curr, shell->env))
		{
			if (!process_invalid_cmd(shell, curr))
				return (0);
		}
		curr = curr->next;
	}
	return (1);
}

/*
 * Processes a single line of user input.
 * Steps:
 *   - Adds input to history for readline recall
 *   - Lexes the input into a list of tokens
 *   - Checks for syntax errors and aborts if any are found
 *   - Parses tokens into a command list
 *   - Expands variables and exit status
 *   - Validates and executes commands if valid
 *   - Frees all temporary data structures
 */
static void	process_input(char *input, t_shell *shell)
{
	t_token		*tokens;
	t_command	*cmd_head;

	tokens = lexer(input);
	if (check_syntax_errors(tokens))
	{
		free_token_list(tokens);
		return ;
	}
	add_history(input);
	cmd_head = parser(tokens);
	expand_all(cmd_head, shell->env, shell->last_exit_status);
	if (validate_all_commands(shell, cmd_head))
		executor(cmd_head, shell);
	free_token_list(tokens);
	free_cmds(cmd_head);
}

/*
 * Main loop of the shell.
 * Repeatedly:
 *   - Reads a line of input from the user.
 *   - Exits gracefully on EOF (Ctrl+D), printing "exit".
 *   - Processes the input if it is not empty.
 *   - Frees the input buffer after processing.
 *   - Clears readline history on exit.
 */
void	minishell_loop(t_shell *shell)
{
	char	*input;

	while (!shell->should_exit)
	{
		input = read_input();
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			process_input(input, shell);
		free(input);
	}
	rl_clear_history();
}
