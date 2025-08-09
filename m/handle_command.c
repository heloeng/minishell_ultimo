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

// void	handle_command(t_data_val *data)
// {
// 	divide_arguments(&data->token, data->text);
// 	/*if (execute_builtin(data))
// 	* {
// 	* free_tokens(&data->token);
// 	* free(data->fd);
// 	* return;
// 	* }*/
//     if (!ft_strchr(data->text, '|') && execute_builtin(data))
//     {
//         free_tokens(&data->token);
//         free(data->fd);
//         return;
//     }
//     exc_command(data);
//     free_tokens(&data->token);
//     free(data->fd);
// }

void	handle_command(t_data_val *data)
{
	divide_arguments(&data->token, data->text);
	if (!ft_strchr(data->text, '|') && execute_builtin(data))
	{
		if (data->token)
		{
			free_tokens(&data->token);
			data->token = NULL;
		}
		if (data->fd)
			free_fd(&data->fd);  
		return;
	}
	exc_command(data);
	free_after_command(data);
}

void free_after_command(t_data_val *data)
{
    if (data->token)
	{
		free_tokens(&data->token);
		data->token = NULL;
	}
    if (data->parser)

		free_parser(data);
    if (data->cmd_path)
	{ 
		free_tokens(&data->cmd_path);
		data->cmd_path = NULL;
	}
    if (data->child_pid){
		free(data->child_pid);
		data->child_pid = NULL;
	}
    if (data->fd)
		free_fd(&data->fd); 
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
	int status_last;

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
	// while (data->fd[i] && i < data->num_pipes)
	while (i < data->num_pipes)
	{
		close(data->fd[i][0]);
		close(data->fd[i][1]);
		i++;
	}
	waitpid(data->child_pid[data->num_pipes], &status_last, 0);
	i = 0;
	while (i < data->num_pipes) {
        waitpid(data->child_pid[i], NULL, 0);
        i++;
    }
	*status = status_last;
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
	if (WIFEXITED(status))
        data->last_exit = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        data->last_exit = 128 + WTERMSIG(status);
    else
        data->last_exit = 1;
}
