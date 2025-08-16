/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10.4-env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:08:15 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/15 21:28:40 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Searches for an environment variable node by key.
 *   - Iterates through the linked list
 *   - Compares keys using ft_strcmp
 *   - Returns pointer to matching node, or NULL if not found
 */
static t_env	*find_env_node(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

/*
 * Updates the value of an existing environment variable node.
 *   - If has_value is true, replaces the old value with the new one
 *   - If has_value is false, frees the unused value string
 */
static void	update_existing_env(t_env *node, char *value, int has_value)
{
	if (has_value)
	{
		free(node->value);
		node->value = value;
	}
	else
		free(value);
}

/*
 * Updates an existing environment variable or adds a new one.
 *   - If key exists in the list, updates its value (if provided)
 *   - If key doesn't exist, creates and appends a new node
 *   - Frees key and value appropriately in both cases
 *   - Returns 0 on success, 1 on allocation failure or invalid input
 */
int	update_or_add_env(t_env **env, char *key, char *value,
	int has_value)
{
	t_env	*node;
	t_env	*new_node;

	if (has_value && !value)
	{
		free(key);
		return (1);
	}
	node = find_env_node(*env, key);
	if (node)
	{
		update_existing_env(node, value, has_value);
		free(key);
	}
	else
	{
		new_node = new_env_node(key, value);
		free(key);
		free(value);
		if (!new_node)
			return (1);
		add_env_back(env, new_node);
	}
	return (0);
}
