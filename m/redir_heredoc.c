/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dydaniel <dydaniel@student.42sp.org.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:16:16 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/11 21:56:19 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_redir_herdoc_aux(t_data_val *data, int *flag, int *j, int i)
{
	if (!ft_strncmp(data->parser[i][*j], "<<", 3))
	{
		*flag = HEREDOC;
		pipe_heredoc(data, data->parser[i], *j, i);
		(*j)++;
	}
	else if (!ft_strncmp(data->parser[i][*j], ">>", 3))
	{
		*flag = APPEND;
		change_fd(data, *flag, i, *j);
		(*j)++;
	}
	else if (!ft_strncmp(data->parser[i][*j], "<", 2))
	{
		*flag = RD_IN;
		change_fd(data, *flag, i, *j);
		(*j)++;
	}
	else if (!ft_strncmp(data->parser[i][*j], ">", 2))
	{
		*flag = RD_OUT;
		change_fd(data, *flag, i, *j);
		(*j)++;
	}
}

int	check_redir_herdoc(t_data_val *data, int i)
{
	int	j;
	int	flag;

	j = 0;
	flag = NO_RD_HD;
	while (data->parser[i][j])
	{
		check_redir_herdoc_aux(data, &flag, &j, i);
		j++;
	}
	return (flag);
}

void	open_file(int *file_fd, int redir_heredoc, \
		char *file_name)
{
	if (redir_heredoc == RD_OUT)
		*file_fd = open(file_name, O_WRONLY | \
				O_CREAT | O_TRUNC, 0644);
	else if (redir_heredoc == RD_IN)
		*file_fd = open(file_name, O_RDONLY);
	else if (redir_heredoc == APPEND)
		*file_fd = open(file_name, O_WRONLY | \
				O_CREAT | O_APPEND, 0644);
}

void	change_fd(t_data_val *data, int redir_heredoc, int i, int j)
{
	int	file_fd;

	file_fd = 0;
	if (!data->parser[i][j + 1])
	{
		printf("Syntax error with abscense of token\n");
		exit (EXIT_FAILURE);
	}
	open_file(&file_fd, redir_heredoc, data->parser[i][j + 1]);
	if (file_fd == -1)
	{
		perror(data->parser[i][j + 1]);
		exit(EXIT_FAILURE);
	}
	if (redir_heredoc == RD_OUT || redir_heredoc == APPEND)
		dup2(file_fd, STDOUT_FILENO);
	else if (redir_heredoc == RD_IN)
		dup2(file_fd, STDIN_FILENO);
	close(file_fd);
}
