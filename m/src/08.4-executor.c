/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08.4-executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:50:05 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/15 21:30:40 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*search_dirs(char *path_dup, char *cmd, char *cmd_path);
static int	try_dir(char *dir, char *cmd,
				char *cmd_path, char *path_dup);

/*
 * Searches for a command in the PATH environment variable.
 *   - Retrieves PATH from the environment
 *   - Duplicates it and allocates space for the full command path
 *   - Calls search_dirs to locate the command
 *   - Returns NULL if allocation fails or command is not found
 */

char	*search_in_path(char *cmd, t_env *env)
{
	char	*path_env;
	char	*path_dup;
	char	*cmd_path;

	path_env = get_env_var(env, "PATH");
	if (!path_env)
		return (NULL);
	path_dup = ft_strdup(path_env);
	if (!path_dup)
		return (NULL);
	cmd_path = malloc(1024);
	if (!cmd_path)
	{
		free(path_dup);
		return (NULL);
	}
	return (search_dirs(path_dup, cmd, cmd_path));
}

/*
 * Iterates through all directories in PATH to find the command.
 *   - Uses ':' as separator to split PATH string
 *   - Tries each directory using try_dir()
 *   - If not found, prints "command not found" and returns NULL
 */
static char	*search_dirs(char *path_dup, char *cmd, char *cmd_path)
{
	char	*dir;
	char	*next_dir;

	dir = path_dup;
	while (dir)
	{
		next_dir = ft_strchr(dir, ':');
		if (next_dir)
		{
			*next_dir = '\0';
			next_dir++;
		}
		if (try_dir(dir, cmd, cmd_path, path_dup))
			return (cmd_path);
		dir = next_dir;
	}
	free(cmd_path);
	free(path_dup);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 21);
	return (NULL);
}

/*
 * Tries to build a full path to the command in a given directory.
 *   - Constructs full path in 'cmd_path'
 *   - Checks if the file exists using access()
 *   - If found, frees path_dup and returns 1
 *   - Otherwise, returns 0
 */
static int	try_dir(char *dir, char *cmd,
	char *cmd_path, char *path_dup)
{
	ft_memset(cmd_path, 0, 1024);
	ft_strcpy(cmd_path, dir);
	if (cmd_path[ft_strlen(cmd_path) - 1] != '/')
		ft_strcat(cmd_path, "/");
	ft_strcat(cmd_path, cmd);
	if (access(cmd_path, F_OK) == 0)
	{
		free(path_dup);
		return (1);
	}
	return (0);
}

/*
 * Validates and executes a command using execve.
 *   - If the path is a directory, prints an error and exits with status 126
 *   - If access is denied, prints an error and exits with status 126
 *   - If execve fails, prints an error and exits with status 127
 */
void	handle_execve(char *cmd_path, char **argv,
	char **envp, struct stat *st)
{
	if (!cmd_path)
		exit(127);
	if (stat(cmd_path, st) == 0 && S_ISDIR(st->st_mode))
	{
		write(2, cmd_path, ft_strlen(cmd_path));
		write(2, ": Is a directory\n", 17);
		free(cmd_path);
		exit(126);
	}
	if (access(cmd_path, X_OK) != 0)
	{
		write(2, cmd_path, ft_strlen(cmd_path));
		write(2, ": Permission denied\n", 20);
		free(cmd_path);
		exit(126);
	}
	if (execve(cmd_path, argv, envp) == -1)
	{
		perror(cmd_path);
		free(cmd_path);
		exit(127);
	}
	free(cmd_path);
}
