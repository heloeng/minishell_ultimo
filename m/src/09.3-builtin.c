/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09.3-builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:35:06 by helde-so          #+#    #+#             */
/*   Updated: 2025/08/15 21:18:45 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Removes an environment variable from the list.
 *   - Searches for a node with key equal to `arg`
 *   - Frees the node and adjusts pointers accordingly
 *   - Returns 0 if found and removed, 1 otherwise
 */
static int	unset_one(char *arg, t_env **env)
{
	t_env	*prev;
	t_env	*curr;

	prev = NULL;
	curr = *env;
	while (curr)
	{
		if (ft_strcmp(curr->key, arg) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free_env_node(curr);
			return (0);
		}
		prev = curr;
		curr = curr->next;
	}
	return (1);
}

/*
 * Implements the 'unset' builtin.
 *   - Iterates over all arguments and removes each variable
 *   - Does not fail on invalid keys (silent by design)
 */
int	builtin_unset(char **argv, t_env **env)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		unset_one(argv[i], env);
		i++;
	}
	return (0);
}

/*
 * Verifies if the given string represents a valid integer number.
 *   - Accepts optional '+' or '-' sign
 *   - Requires at least one digit
 *   - Returns 1 if valid, 0 otherwise
 */
static int	is_valid_number(const char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit((unsigned char)arg[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
 * Implements the 'exit' builtin:
 *   - If too many arguments are given, prints an error and does not exit.
 *   - If a single argument is given, validates it as a number
 * 		and exits with its value.
 *   - If the argument is not a valid number, prints error and exits with code 2.
 *   - If no argument is given, exits with the shell's last exit status.
 */
int	builtin_exit(char **argv, t_shell *shell)
{
	int	code;

	if (argv[1] && argv[2])
	{
		write(2, " too many arguments\n", 20);
		shell->last_exit_status = 1;
		return (0);
	}
	if (argv[1] && !is_valid_number(argv[1]))
	{
		write(2, " numeric argument required\n", 27);
		shell->should_exit = 1;
		shell->exit_code = 2;
		return (1);
	}
	if (argv[1])
		code = ft_atol(argv[1]);
	else
		code = shell->last_exit_status;
	shell->should_exit = 1;
	shell->exit_code = (unsigned char)code;
	return (1);
}
