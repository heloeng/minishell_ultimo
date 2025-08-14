/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configure_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:01:49 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/13 20:19:25 by helde-so         ###   ########.fr       */
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
	g_exit_status = 130; //ALTEREI AQUI/// ---------------
}

void	configure_signal(void)
{
	signal(SIGINT, handle_ctrlc);//TRATA CTRL+C 
	signal(SIGQUIT, SIG_IGN);//IGNORA CTRL+C
}

void change_signal_exec(t_data_val *data, int *status)
{
	int sig;
	if (WIFEXITED(*status))
	{
		data->last_exit = WEXITSTATUS(*status);
	/*else if (WIFSIGNALED(*status))
		data->last_exit = 128 + WTERMSIG(*status);*/
	}
	else if (WIFSIGNALED(*status))
	{
		sig = WTERMSIG(*status);
		data->last_exit = 128 + sig;

		if (sig == SIGINT) // Ctrl+C
			write(STDOUT_FILENO, "\n", 1);
		else if (sig == SIGQUIT) /* Ctrl+ \ */
			write(STDERR_FILENO, "Quit (core dumped)\n", 19);
	}	
	g_exit_status = data->last_exit;
}
	
	
void	configure_signal_childs(void)
{
	signal(SIGINT, SIG_DFL); 
	signal(SIGQUIT, SIG_DFL);
}