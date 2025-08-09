/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dydaniel <dydaniel@student.42sp.org.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:53:18 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/05 22:30:42 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_fd(int ***fd)
{
	int	i;

	i = 0;
	while ((*fd)[i])
	{
		free((*fd)[i]);
		i++;
	}
	free((*fd));
	(*fd) = NULL;
}

void	free_data_aux(t_data_val *data)
{
	if (data->path)
	{
		free(data->path);
		data->path = NULL;
	}
	if (data->envp_path)
	{
		free(data->envp_path);
		data->envp_path = NULL;
	}
	if (data->cmd_path)
	{
		free_tokens(&data->cmd_path);
		data->cmd_path = NULL;
	}
	if (data->child_pid)
	{
		free(data->child_pid);
		data->child_pid = NULL;
	}
}

void	free_data(t_data_val *data)
{
	if (data->envp)
		free_tokens(&data->envp);
	if (data->text)
		free(data->text);
	if (data->token)
		free_tokens(&data->token);
	if (data->parser)
		free_parser(data);
	free_data_aux(data);
	if (data->fd)
		free_fd(&data->fd);
}
