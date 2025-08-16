/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09.4-builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 11:07:39 by helde-so          #+#    #+#             */
/*   Updated: 2025/08/15 21:20:32 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Expands the '~' character or handles a missing argument by retrieving $HOME.
 *   - If arg is NULL, duplicates $HOME into path.
 *   - If arg starts with '~', joins $HOME with the rest of the path (after '~').
 *   - If $HOME is not set, prints an error and returns 1.
 *   - On success, path receives a dynamically allocated string and returns 0.
 */
static int	cd_expand_path(char *arg, t_shell *shell, char **path)
{
	char	*home;

	home = get_env_var(shell->env, "HOME");
	if (!home)
	{
		write(2, "cd: HOME not set\n", 18);
		shell->last_exit_status = 1;
		return (1);
	}
	if (arg == NULL)
		*path = ft_strdup(home);
	else
		*path = ft_strjoin(home, arg + 1);
	return (0);
}

/*
 * Handles the arguments passed to the 'cd' builtin.
 *   - If more than one argument is provided, prints an error and returns 1.
 *   - If no argument is given, uses $HOME as the target directory.
 *   - If the argument starts with '~', expands it using $HOME.
 *   - Otherwise, duplicates the argument as-is into path.
 *   - On success, path receives a dynamically allocated string and returns 0.
 */
static int	cd_handle_args(char **argv, t_shell *shell, char **path)
{
	if (argv[2] != NULL)
	{
		write(2, "cd: too many arguments\n", 23);
		shell->last_exit_status = 1;
		return (1);
	}
	if (argv[1] == NULL)
		return (cd_expand_path(NULL, shell, path));
	else if (argv[1][0] == '~')
		return (cd_expand_path(argv[1], shell, path));
	else
		*path = ft_strdup(argv[1]);
	return (0);
}

/*
 * Updates PWD and OLDPWD in the environment after a successful 'cd'.
 *   - Adds or updates OLDPWD with the previous working directory.
 *   - Adds or updates PWD with the new current directory.
 *   - Frees the newpwd string after updating.
 */
static void	cd_update_pwd(t_env **env, char *oldpwd, char *newpwd)
{
	if (oldpwd)
		update_or_add_env(env, ft_strdup("OLDPWD"), ft_strdup(oldpwd), 1);
	if (newpwd)
		update_or_add_env(env, ft_strdup("PWD"), ft_strdup(newpwd), 1);
	free(newpwd);
}

/*
 * Implements the 'cd' builtin.
 *   - Validates arguments and resolves the target path.
 *   - Calls chdir() to change the current directory.
 *   - Updates PWD and OLDPWD environment variables.
 *   - Frees dynamically allocated path.
 *   - Sets shell->last_exit_status to 0 on success or 1 on failure.
 */
int	builtin_cd(char **argv, t_shell *shell)
{
	char	*path;
	char	*oldpwd;
	char	*newpwd;

	if (cd_handle_args(argv, shell, &path))
		return (1);
	oldpwd = get_env_var(shell->env, "PWD");
	if (chdir(path) != 0)
	{
		perror("cd");
		free(path);
		shell->last_exit_status = 1;
		return (1);
	}
	newpwd = getcwd(NULL, 0);
	cd_update_pwd(&shell->env, oldpwd, newpwd);
	free(path);
	shell->last_exit_status = 0;
	return (0);
}
