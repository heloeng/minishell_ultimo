/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02-signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:01:49 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/15 21:16:15 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Signal handler for SIGINT (Ctrl+C) during interactive mode.
 * If the program is currently waiting for user input (g_in_prompt is set),
 * it clears the current line, moves to a new line, and redraws the prompt,
 * effectively simulating a "clean cancel" of the current input.
 * If not in prompt mode, it simply prints a newline.
 * The signal number 'sig' is unused and cast to void to avoid compiler warnings.
 */
static void	sigint_handler(int sig)
{
	(void)sig;
	if (g_in_prompt != 0)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
		write(1, "\n", 1);
}

/*
 * Sets up signal handling for the shell:
 *   - SIGINT (Ctrl+C) is handled by 'sigint_handler'
 *   - SIGQUIT (Ctrl+\) is ignored
 */
void	handle_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
