/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_childs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 10:21:09 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/13 20:06:25 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_unused_fd(t_data_val *data, int i)
{
	int	k;

	k = 0;
	while (k < data->num_pipes)
	{
		if (k != i - 1)
			close(data->fd[k][0]);
		if (k != i)
			close(data->fd[k][1]);
		k++;
	}
}

void	exec_child_process(t_data_val *data, int i)
{
	int	redir_heredoc;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	redir_heredoc = check_redir_herdoc(data, i);
	if (i == 0)
		first_pipe(data, redir_heredoc, i);
	else if (i == data->num_pipes)
		last_pipe(data, redir_heredoc, i);
	else
		middles_pipe(data, redir_heredoc, i);
	if (check_builtin(data->parser[i][0]))
	{
		data->last_exit = execute_builtin(data, data->parser[i]);
		exit(data->last_exit);
	}
	if (!data->cmd_path[i])
	{
		printf("command not found: %s\n", data->parser[i][0]);
		exit(127);
	}
	else
		execve(data->cmd_path[i], data->parser[i], data->envp);
	perror("execve falhou");
	free_data(data);
	exit(1);
}

void	one_command_child(t_data_val *data, int i, int flag)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	while (data->token[i])
	{
		if (data->token[i][0] == '>' || data->token[i][0] == '<')
		{
			flag = solo_command_redir_heredoc(data->token, i);
			break ;
		}
		i++;
	}
	if (flag != NO_RD_HD)
		data->token = clear_parser(data->token);
	if (check_builtin(data->token[0]))
	{
		if (execute_builtin(data, data->token) == 1)
			exit(0);
	}
	if (!data->cmd_path[0])
	{
		perror("command not found");
		exit(127);
	}
	execve(data->cmd_path[0], data->token, data->envp);
	perror("execve");
	exit(1);
}

void	exec_one_command(t_data_val *data, int *status)
{
	int	i;
	int	flag;

	i = 0;
	flag = NO_RD_HD;
	//Antes do fork verifica se o comando é cd/export/unset/exit. //se for builtin do pai executa sem fork
	if (run_parent_builtin_single(data, status))//!alterei aqui
		return ;
	data->child_pid[0] = fork();
	if (data->child_pid[0] == 0)
	{
		one_command_child(data, i, flag);
	}
	else if (data->child_pid[0] > 0)
	{
		waitpid(data->child_pid[0], status, 0);
		if (WIFEXITED(*status))
			g_exit_status = WEXITSTATUS(*status);
		else if (WIFSIGNALED(*status))
			g_exit_status = 128 + WTERMSIG(*status);
		data->last_exit = g_exit_status;
		change_signal_exec(data, status);
	}
	else
		perror("fork");
}


