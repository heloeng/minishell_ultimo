/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04-readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:54:54 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/15 21:48:06 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Reads a line of input from the user using the readline library.
 *
 * While the shell is waiting for user input (i.e., displaying the prompt),
 * the global variable `g_in_prompt` is set to indicate that readline is active.
 * This allows SIGINT handler to behave appropriately when user presses Ctrl+C,
 * avoiding issues like duplicate prompts or improper cursor handling.
 *
 * Prompt displayed: "minishell >> "
 *
 * Returns:
 *   - A pointer to the input string (must be freed by the caller)
 *   - NULL if EOF is encountered (e.g., the user presses Ctrl+D)
 */
char	*read_input(void)
{
	char	*input;

	g_in_prompt = 1;
	input = readline("minishell >> ");
	g_in_prompt = 0;
	if (!input)
		return (NULL);
	return (input);
}
