/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08.2-executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:58:11 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/15 21:29:50 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_command(t_command *current_cmd, char **envp,
				t_shell *shell);

/*
 * Sets up a pipe (if needed) and forks the current process.
 *   - Creates a pipe if there is a next command in the pipeline
 *   - Forks and returns the child PID
 *   - Exits on error
 */
pid_t	setup_pipe_and_fork(t_command *current_cmd, int *pipefd)
{
	pid_t	pid;

	if (current_cmd->next)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

/*
 * Executes a single command in a child process.
 *   - Sets up stdin from the previous pipe if needed
 *   - Sets up stdout to the next pipe if in a pipeline
 *   - Calls execute_command to handle redirections and execution
 *   - Exits the child process after execution
 */
void	execute_single_command(t_command *current_cmd, char **envp,
	t_shell *shell, t_exec_data *data)
{
	if (data->prev_fd != -1)
		dup_and_close(data->prev_fd, STDIN_FILENO);
	if (current_cmd->next)
	{
		dup_and_close(data->pipefd[1], STDOUT_FILENO);
		close(data->pipefd[0]);
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execute_command(current_cmd, envp, shell);
	exit(0);
}

/*
 * Handles cleanup and setup in the parent process after a fork.
 *   - Stores last child's PID
 *   - Closes previous input pipe (if open)
 *   - Sets up the input file descriptor for the next command
 */
void	handle_parent_process(t_command *current_cmd, pid_t pid,
	t_exec_data *data)
{
	data->last_pid = pid;
	if (data->prev_fd != -1)
		close(data->prev_fd);
	if (current_cmd->next)
	{
		close(data->pipefd[1]);
		data->prev_fd = data->pipefd[0];
	}
}

/*
 * Duplicates a file descriptor and closes the original if needed.
 *   - If oldfd and newfd are different, duplicates oldfd into newfd
 *   - Closes oldfd to avoid file descriptor leaks
 */
void	dup_and_close(int oldfd, int newfd)
{
	if (oldfd != newfd)
	{
		dup2(oldfd, newfd);
		close(oldfd);
	}
}

/*
 * Executes a command, handling redirections, built-ins, and external binaries.
 *   - Applies redirections before execution
 *   - If command is empty, exits quietly
 *   - If built-in, executes it and exits
 *   - If command starts with '/' or '.', uses it as a path
 *   - Otherwise, searches the command in the PATH
 *   - Calls handle_execve to validate and execute the binary
 */
static void	execute_command(t_command *current_cmd, char **envp, t_shell *shell)
{
	char		*cmd_path;
	struct stat	st;

	handle_redirections(current_cmd->redirects);
	if (!current_cmd->argv[0] || current_cmd->argv[0][0] == '\0')
		exit(0);
	if (is_builtin(current_cmd->argv[0]))
	{
		exec_builtin(current_cmd, shell);
		exit(0);
	}
	if (current_cmd->argv[0][0] == '/' || current_cmd->argv[0][0] == '.')
	{
		if (access(current_cmd->argv[0], F_OK) == 0)
			cmd_path = ft_strdup(current_cmd->argv[0]);
		else
		{
			write(2, current_cmd->argv[0], ft_strlen(current_cmd->argv[0]));
			write(2, ": No such file or directory\n", 29);
			exit(127);
		}
	}
	else
		cmd_path = search_in_path(current_cmd->argv[0], shell->env);
	handle_execve(cmd_path, current_cmd->argv, envp, &st);
}
