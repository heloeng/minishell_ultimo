/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10.1-env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:08:15 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/15 21:21:48 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Splits a string of the format "KEY=VALUE" into key and value.
 *   - If '=' is found, key is substring before '=', value is after
 *   - If '=' is not found, entire string is considered the key
 *   - Allocates memory for key and value; returns 1 on success, 0 on failure
 */
static int	split_env_entry(char *env_line, char **key, char **value)
{
	char	*equal;
	int		len;

	equal = ft_strchr(env_line, '=');
	if (equal)
	{
		len = equal - env_line;
		*key = malloc(len + 1);
		if (!*key)
			return (0);
		ft_strncpy(*key, env_line, len);
		(*key)[len] = '\0';
		*value = ft_strdup(equal + 1);
	}
	else
	{
		*key = ft_strdup(env_line);
		*value = NULL;
	}
	if (!*key || (equal && !*value))
		return (0);
	return (1);
}

/*
 * Creates a new environment variable node.
 *   - Duplicates key and value strings
 *   - Initializes next to NULL
 *   - Returns pointer to new node, or NULL on failure
 */
t_env	*new_env_node(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}

/*
 * Adds a new environment node to the end of the linked list.
 *   - If the list is empty, sets new_node as the head
 *   - Otherwise, traverses to the end and appends new_node
 */
void	add_env_back(t_env **env_list, t_env *new_node)
{
	t_env	*tmp;

	if (!*env_list)
	{
		*env_list = new_node;
		return ;
	}
	tmp = *env_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

/*
 * Creates the linked list of environment variables from envp.
 *   - For each string in envp, splits into key and value
 *   - Creates a new t_env node and appends it to the list
 *   - Returns the head of the list, or NULL on failure
 */
t_env	*create_env_list(char **envp)
{
	t_env	*env_list;
	t_env	*new_node;
	char	*key;
	char	*value;
	int		ok;

	env_list = NULL;
	while (*envp)
	{
		ok = split_env_entry(*envp, &key, &value);
		if (!ok)
			return (NULL);
		new_node = new_env_node(key, value);
		free(key);
		free(value);
		if (!new_node)
			return (NULL);
		add_env_back(&env_list, new_node);
		envp++;
	}
	return (env_list);
}
