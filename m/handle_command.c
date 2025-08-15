/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:58:11 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/05 22:18:27 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void handle_exit(t_data_val *data)
{
	if (errno == ENOENT)
		data->last_exit = ENOENT;
	else if(errno == EINTR)
		data->last_exit == EINTR;
	else if (errno == EACCES)
		data->last_exit == EACCES;
	else if (errno == ENOTDIR)
		data->last_exit = ENOTDIR;

}*/




void	handle_command(t_data_val *data)
{
	divide_arguments(&data->token, data->text);
	exc_command(data);
}

void	close_fds(int **fd, int i)
{
	int	j;

	j = 0;
	while (fd[j])
	{
		if (j != i)
		{
			close(fd[j][0]);
			close(fd[j][1]);
		}
		i++;
	}
}

void	exec_pipes(t_data_val *data, int i, int *status)
{
	int j;

	j = 0;
	while (i <= data->num_pipes)
	{
		data->child_pid[i] = fork();
		if (data->child_pid[i] < 0)
			printf("ERROR ON CREATING CHILD PROCESS!\n");
		else if (data->child_pid[i] == 0)
			exec_child_process(data, i);
		i++;
	}
	i = 0;
	while (data->fd[i] && i <= data->num_pipes)
	{
		close(data->fd[i][0]);
		close(data->fd[i][1]);
		i++;
	}
	i = 0;
	while (data->child_pid[i] && i <= data->num_pipes)
	{
		waitpid(data->child_pid[i], status, 0);
		if (WIFEXITED(*status) && WEXITSTATUS(*status) != 0)
		{
			j = i;
			while(j <= data->num_pipes)
			{
				kill(data->child_pid[j], SIGKILL);
				j++;
			}
		}
		else if (i == data->num_pipes && WIFEXITED(*status))
			data->last_exit = WEXITSTATUS(*status);
		//change_signal_exec(data, status);
		i++;
	}
}

void	exc_command(t_data_val *data)
{
	int	i;
	int	status;

	i = 0;
	parse_token(&data);
	get_full_path(&data);
	data->child_pid = malloc(sizeof(pid_t) * (data->num_pipes + 1));
	if (!data->child_pid)
		printf("ERROR\n");
	if (data->parser)
		exec_pipes(data, i, &status);
	else
		exec_one_command(data, &status);
}
