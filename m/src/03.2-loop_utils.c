/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03.2-loop_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:58:11 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/15 21:18:15 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Checks if a command can be executed directly as-is (absolute or relative
 * path), or if it's a builtin. Returns:
 *   1  - if command is valid and accessible
 *   0  - if path command is invalid
 *  -1  - if command must be searched in PATH
 */
static int	validate_direct_command(t_command *cmd)
{
	if (!cmd->argv[0] || cmd->argv[0][0] == '\0')
		return (1);
	if (is_builtin(cmd->argv[0]))
		return (1);
	if (cmd->argv[0][0] == '/' || cmd->argv[0][0] == '.')
	{
		if (access(cmd->argv[0], F_OK) == 0)
			return (1);
		else
			return (0);
	}
	return (-1);
}

/*
 * Checks if a given command exists in a specific directory.
 * Constructs the full path in `cmd_path` and tests its existence.
 * Returns 1 if found, 0 otherwise.
 */
static int	check_cmd_in_dir(char *dir, char *cmd_name, char *cmd_path)
{
	size_t	len;

	ft_memset(cmd_path, 0, 1024);
	ft_strcpy(cmd_path, dir);
	len = ft_strlen(cmd_path);
	if (len > 0 && cmd_path[len - 1] != '/')
		ft_strcat(cmd_path, "/");
	ft_strcat(cmd_path, cmd_name);
	if (access(cmd_path, F_OK) == 0)
		return (1);
	return (0);
}

/*
 * Searches for the command in all directories specified in the PATH variable.
 * Returns 1 if the command is found in any of the PATH directories, 0 otherwise.
 */
static int	search_cmd_in_path(char *cmd_name, char *path)
{
	char	*cmd_path;
	char	*dir;
	char	*next_dir;

	cmd_path = malloc(1024);
	if (!cmd_path)
		return (0);
	dir = path;
	while (dir)
	{
		next_dir = ft_strchr(dir, ':');
		if (next_dir)
		{
			*next_dir = '\0';
			next_dir++;
		}
		if (check_cmd_in_dir(dir, cmd_name, cmd_path))
		{
			free(cmd_path);
			return (1);
		}
		dir = next_dir;
	}
	free(cmd_path);
	return (0);
}

/*
 * Validates if a given command can be executed:
 * - First checks if it's a builtin or direct path (./, /bin/ls, etc)
 * - If not, searches for the command in the PATH
 * Returns 1 if command is executable, 0 otherwise.
 */
int	is_command_valid(t_command *cmd, t_env *env)
{
	char	*path_env;
	char	*path;
	int		result;

	result = validate_direct_command(cmd);
	if (result != -1)
		return (result);
	path_env = get_env_var(env, "PATH");
	if (!path_env)
		return (0);
	path = ft_strdup(path_env);
	if (!path)
		return (0);
	result = search_cmd_in_path(cmd->argv[0], path);
	free(path);
	return (result);
}

/*
 * Handles the case when a command is not valid or not found.
 * Prints a 'command not found' error if the path does not exist.
 * Sets the shell's last exit status to 127.
 * Returns 1 if the command is technically accessible (but maybe invalid), 
 * 0 otherwise.
 */
int	process_invalid_cmd(t_shell *shell, t_command *cmd)
{
	if (cmd->argv[0][0] == '/' || cmd->argv[0][0] == '.')
	{
		if (access(cmd->argv[0], F_OK) != 0)
		{
			perror(cmd->argv[0]);
			if (shell)
				shell->last_exit_status = 127;
			return (0);
		}
		else
			return (1);
	}
	write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
	write(2, ": command not found\n", 20);
	if (shell)
		shell->last_exit_status = 127;
	return (0);
}
