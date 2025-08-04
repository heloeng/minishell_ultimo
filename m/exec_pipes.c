/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dydaniel <dydaniel@student.42sp.org.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:08:17 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/02 16:08:19 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void first_pipe(t_data_val *data, int flag, int i)
{
    if (flag == NO_RD_HD)
    {
        close(data->fd[0][0]);
        dup2(data->fd[0][1], STDOUT_FILENO);
        close(data->fd[0][1]);
    }
    else
        data->parser[i] = clear_parser(data->parser[i]);
    close_unused_fd(data, i);
}

void middles_pipe(t_data_val *data, int flag, int i)
{
    if (flag == NO_RD_HD)
    {
        dup2(data->fd[i-1][0], STDIN_FILENO);
        close(data->fd[i-1][0]);
        dup2(data->fd[i][1], STDOUT_FILENO);
        close(data->fd[i][1]);
    }
    else
        data->parser[i] = clear_parser(data->parser[i]);
    close_unused_fd(data, i);
}

void last_pipe(t_data_val *data, int flag, int i)
{
    if (flag == NO_RD_HD)
    {
        close(data->fd[i-1][1]); // fecha escrita que não usa
        dup2(data->fd[i-1][0], STDIN_FILENO);                   
        close(data->fd[i-1][0]);
    }
    else
        data->parser[i] = clear_parser(data->parser[i]);
    close_unused_fd(data, i);
}
