/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo_redir_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dydaniel <dydaniel@student.42sp.org.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:50:05 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/05 22:00:06 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	solo_append(char **token, int *i, int *flag, int *fd)
{
	*flag = APPEND;
	*fd = open(token[(*i) + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd == -1)
	{
		perror(token[(*i) + 1]);
		close(*fd);
		exit(1);
	}
	(*i)++;
}

void	solo_redir_in(char **token, int *i, int *flag, int *fd)
{
	*flag = RD_IN;
	*fd = open(token[(*i) + 1], O_RDONLY);
	if (*fd == -1)
	{
		perror(token[(*i) + 1]);
		exit(1);
	}
	(*i)++;
}

void	solo_redir_out(char **token, int *i, int *flag, int *fd)
{
	*flag = RD_OUT;
	*fd = open(token[(*i) + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd == -1)
	{
		perror(token[(*i) + 1]);
		exit(1);
	}
	(*i)++;
}

void	solo_heredoc(char **token, int *i, int *flag, int *fd)
{
	*flag = HEREDOC;
	solo_heredoc_fd(token, *i, fd);
	dup2(*fd, STDIN_FILENO);
	(*i)++;
}

int	solo_command_redir_heredoc(char **token, int i)
{
	int	flag;
	int	file_fd;

	flag = NO_RD_HD;
	while (token[i])
	{
		if (!ft_strncmp(token[i], "<<", 3))
			solo_heredoc(token, &i, &flag, &file_fd);
		else if (!ft_strncmp(token[i], ">>", 3))
			solo_append(token, &i, &flag, &file_fd);
		else if (!ft_strncmp(token[i], "<", 2))
			solo_redir_in(token, &i, &flag, &file_fd);
		else if (!ft_strncmp(token[i], ">", 2))
			solo_redir_out(token, &i, &flag, &file_fd);
		if (flag == RD_OUT || flag == APPEND)
			dup2(file_fd, STDOUT_FILENO);
		else if (flag == RD_IN)
			dup2(file_fd, STDIN_FILENO);
		close(file_fd);
		i++;
	}
	return (flag);
}
