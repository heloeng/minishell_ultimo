/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08.3-executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:16:16 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/15 21:30:18 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_heredoc(char *limiter, int *fd_read);
static void	open_and_dup_in(char *file);
static void	open_and_dup_out(char *file, int type);

/*
 * Processes all redirections for a command.
 * Handles heredoc, input, and output redirections.
 * Applies each redirection by opening files or creating heredoc pipes.
 */
void	handle_redirections(t_redirect *redir)
{
	int	fd;

	while (redir)
	{
		if (redir->type == T_HEREDOC)
		{
			handle_heredoc(redir->file, &fd);
			dup_and_close(fd, STDIN_FILENO);
		}
		else if (redir->type == T_REDIR_IN)
			open_and_dup_in(redir->file);
		else
			open_and_dup_out(redir->file, redir->type);
		redir = redir->next;
	}
}

/*
 * Handles heredoc redirection by reading lines until the limiter is found.
 * Writes the input into a pipe and sets the read end for STDIN redirection.
 */
static void	handle_heredoc(char *limiter, int *fd_read)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		line = readline("heredoc> ");
		if (!line || ft_strcmp(line, limiter) == 0)
			break ;
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	free(line);
	close(pipe_fd[1]);
	*fd_read = pipe_fd[0];
}

/*
 * Opens an input file and duplicates its file descriptor to STDIN.
 * Exits with an error message if the file cannot be opened.
 */
static void	open_and_dup_in(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror(file);
		exit(EXIT_FAILURE);
	}
	dup_and_close(fd, STDIN_FILENO);
}

/*
 * Opens an output file and duplicates its file descriptor to STDOUT.
 * Uses truncation or appending based on redirection type.
 * Exits with an error message if the file cannot be opened.
 */
static void	open_and_dup_out(char *file, int type)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (type == T_REDIR_OUT)
		flags |= O_TRUNC;
	if (type == T_APPEND)
		flags |= O_APPEND;
	fd = open(file, flags, 0644);
	if (fd < 0)
	{
		perror(file);
		exit(EXIT_FAILURE);
	}
	dup_and_close(fd, STDOUT_FILENO);
}
