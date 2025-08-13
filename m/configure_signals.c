/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configure_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dydaniel <dydaniel@student.42sp.org.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:01:49 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/11 23:02:24 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_ctrlc(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	configure_signal()
{
	signal(SIGINT, handle_ctrlc);
	signal(SIGQUIT, SIG_IGN);
}

void change_signal_exec(t_data_val *data, int *status)
{
	if (WIFEXITED(*status))
		data->last_exit = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		data->last_exit = 128 + WTERMSIG(*status);
}