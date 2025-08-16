/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01-main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:54:54 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/15 21:15:57 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_in_prompt = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	((void)argc, (void)argv);
	shell.env = create_env_list(envp);
	shell.last_exit_status = 0;
	shell.should_exit = 0;
	shell.exit_code = 0;
	handle_signals();
	minishell_loop(&shell);
	rl_clear_history();
	free_env_list(shell.env);
	exit(shell.exit_code);
}
