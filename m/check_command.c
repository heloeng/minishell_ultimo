/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:58:11 by dydaniel          #+#    #+#             */
/*   Updated: 2025/07/05 17:42:24 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_command(t_data_val *data)
{
    divide_arguments(&data->token, data->text);
    if (execute_builtin(data))
    {
        free_tokens(&data->token);
        free(data->fd);
        return;
    }
    // if (check_redir_herdoc(data->token))
    // {
    //     ft_printf("pode chamar herdioc\n");
    // }
    exc_command(data);
    free_tokens(&data->token);
    free(data->fd); 
}

void close_fds(int **fd, int i)
{
    int j;

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

void exc_command(t_data_val *data)
{
    int i;
    //int j;
    int status;

    i = 0;
    //j = 0;
    parse_token(&data);
    get_full_path(&data);
    data->child_pid = malloc(sizeof(pid_t) * (data->num_pipes + 1));
    if (!data->child_pid)
        ft_printf("ERROR\n");
    if (data->parser)
    {
        while (i <= data->num_pipes)
        {
            data->child_pid[i] = fork();
            if (data->child_pid[i] < 0)
                ft_printf("ERROR ON CREATING CHILD PROCESS!\n");
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
            waitpid(data->child_pid[i], &status, 0);
            i++;
        }
    }
    else
        exec_one_command(data, &status);
    free_parser(data);         
}
