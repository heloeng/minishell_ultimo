/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09.1-builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:12:03 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/15 21:17:29 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Implements the 'echo' builtin.
 *   - Supports the '-n' option to suppress the newline
 *   - Prints all arguments separated by spaces
 */
static int	builtin_echo(char **argv)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (argv[i] && ft_strcmp(argv[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}

/*
 * Implements the 'pwd' builtin.
 *   - Prints the current working directory
 *   - Uses getcwd() to retrieve the directory
 */
static int	builtin_pwd(void)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		perror("pwd");
	return (0);
}

/*
 * Implements the 'env' builtin.
 *   - Prints all environment variables in the form key=value
 *   - Skips variables without a value
 */
static int	builtin_env(t_env *env)
{
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

/*
 * Executes a builtin command.
 *   - Matches the command string with supported builtins
 *   - Updates shell's last_exit_status when appropriate
 *   - Handles special cases (cd, export, unset, exit) separately
 */
void	exec_builtin(t_command *current_cmd, t_shell *shell)
{
	if (ft_strcmp(current_cmd->argv[0], "echo") == 0)
		shell->last_exit_status = builtin_echo(current_cmd->argv);
	else if (ft_strcmp(current_cmd->argv[0], "cd") == 0)
		builtin_cd(current_cmd->argv, shell);
	else if (ft_strcmp(current_cmd->argv[0], "pwd") == 0)
		shell->last_exit_status = builtin_pwd();
	else if (ft_strcmp(current_cmd->argv[0], "export") == 0)
		builtin_export(current_cmd->argv, &shell->env, shell);
	else if (ft_strcmp(current_cmd->argv[0], "unset") == 0)
		builtin_unset(current_cmd->argv, &shell->env);
	else if (ft_strcmp(current_cmd->argv[0], "env") == 0)
		shell->last_exit_status = builtin_env(shell->env);
	else if (ft_strcmp(current_cmd->argv[0], "exit") == 0)
		builtin_exit(current_cmd->argv, shell);
}
