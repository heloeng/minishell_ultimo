/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08.1-executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:35:13 by helde-so          #+#    #+#             */
/*   Updated: 2025/08/15 21:29:32 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Checks if the command is a simple built-in that can be executed directly.
 *   - Must be a built-in command
 *   - Must not be part of a pipeline (i.e., no next command)
 *   - Must not have any redirections
 *   - If all conditions are met, executes the built-in and returns 1
 *   - Otherwise, returns 0
 */
static int	handle_simple_builtin(t_command *current_cmd, t_shell *shell)
{
	if (is_builtin(current_cmd->argv[0]) && !current_cmd->next
		&& !current_cmd->redirects)
	{
		exec_builtin(current_cmd, shell);
		return (1);
	}
	return (0);
}

/*
 * Executes a single command within a pipeline.
 *   - Converts the environment list to an array for execve
 *   - Sets up pipes and forks the process
 *   - In the child, executes the command
 *   - In the parent, handles bookkeeping for the forked process
 *   - Frees the environment array after execution
 */
static void	execute_pipeline_command(t_command *current_cmd, t_shell *shell,
	t_exec_data *data)
{
	pid_t	pid;
	char	**env_array;

	env_array = env_list_to_array(shell->env);
	if (!env_array)
	{
		perror("malloc");
		return ;
	}
	pid = setup_pipe_and_fork(current_cmd, data->pipefd);
	if (pid == 0)
		execute_single_command(current_cmd, env_array, shell, data);
	else
		handle_parent_process(current_cmd, pid, data);
	free_env_array(env_array);
}

/*
 * Waits for the last process in the pipeline and updates the shell status.
 *   - Waits for the last PID to retrieve its exit or signal status
 *   - Sets the shell's last_exit_status accordingly
 *   - Continues waiting for any remaining child processes
 */
static void	wait_for_processes(pid_t last_pid, t_shell *shell)
{
	int	status;
	int	sig;

	waitpid(last_pid, &status, 0);
	if (WIFEXITED(status))
		shell->last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		shell->last_exit_status = 128 + sig;
		if (sig == SIGQUIT)
			write(1, "Quit (core dumped)\n", 20);
	}
	while (wait(NULL) > 0)
		;
}

/*
 * Main execution loop for a list of commands.
 *   - Iterates over each command node
 *   - If the command is a simple built-in, executes and returns early
 *   - Otherwise, executes it as part of a pipeline
 *   - After all commands are handled, waits for the last process to finish
 */
void	executor(t_command *cmd_head, t_shell *shell)
{
	t_command		*current_cmd;
	t_exec_data		data;

	current_cmd = cmd_head;
	data.prev_fd = -1;
	data.last_pid = -1;
	while (current_cmd)
	{
		if (handle_simple_builtin(current_cmd, shell))
			return ;
		execute_pipeline_command(current_cmd, shell, &data);
		current_cmd = current_cmd->next;
	}
	wait_for_processes(data.last_pid, shell);
}
