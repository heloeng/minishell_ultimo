/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10.5-env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:53:18 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/15 21:29:04 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Frees the entire linked list of environment variables.
 *   - Iterates through the list
 *   - Frees each node using free_env_node
 */
void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free_env_node(env);
		env = tmp;
	}
}

/*
 * Frees a single environment variable node.
 *   - Frees key, value, and the node itself
 */
void	free_env_node(t_env *env)
{
	if (env)
	{
		free(env->key);
		free(env->value);
		free(env);
	}
}

/*
 * Retrieves the value of an environment variable by key.
 *   - Searches the linked list for a matching key
 *   - Returns the value if found, or NULL if not found
 */
char	*get_env_var(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

/*
 * Frees a NULL-terminated array of environment strings.
 *   - Frees each string in the array
 *   - Frees the array itself
 */
void	free_env_array(char **env_array)
{
	int	i;

	i = 0;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}
