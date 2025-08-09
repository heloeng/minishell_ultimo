/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dydaniel <dydaniel@student.42sp.org.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 20:53:39 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/05 22:13:31 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_heredoc(t_data_val *data, char **parser, int j, int i)
{
	char	*delimiter;
	char	*hd_line;
	int		size;

	delimiter = parser[j + 1];
	dup2(data->fd[i][0], STDIN_FILENO);
	close(data->fd[i][0]);
	while (1)
	{
		hd_line = readline(">");
		size = ft_strlen(hd_line);
		write(data->fd[i][1], hd_line, size);
		add_history(hd_line);
		if (!ft_strncmp(delimiter, hd_line, size))
			break ;
		free(hd_line);
	}
}

void	solo_heredoc_fd(char **token, int i, int *fd)
{
	char	*delimiter;
	char	*hd_line;
	int		size;
	int		pipe_fd[2];

	delimiter = token[i + 1];
	pipe(pipe_fd);
	while (1)
	{
		hd_line = readline(">");
		if (!hd_line)
			break ;
		size = ft_strlen(delimiter);
		if (ft_strcmp(delimiter, hd_line) == 0)
			break ;
		size = ft_strlen(hd_line);
		write(pipe_fd[1], hd_line, size);
		write(pipe_fd[1], "\n", 1);
		add_history(hd_line);
		free(hd_line);
	}
	if (hd_line)
		free(hd_line);
	close(pipe_fd[1]);
	*fd = pipe_fd[0];
}
