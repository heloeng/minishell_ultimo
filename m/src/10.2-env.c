/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10.2-env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:06:29 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/15 21:25:53 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Counts the number of environment variables in the list.
 *   - If with_value_only is non-zero, counts only nodes with a value
 *   - Otherwise, counts all nodes
 *   - Returns the total count
 */
int	count_env(t_env *env, int with_value_only)
{
	int	count;

	count = 0;
	while (env)
	{
		if (!with_value_only || env->value)
			count++;
		env = env->next;
	}
	return (count);
}

/*
 * Joins a key and value into a "key=value" string.
 *   - Allocates memory for the resulting string
 *   - Returns the new string, or NULL on failure
 */
static char	*join_key_value(char *key, char *value)
{
	int		len;
	char	*str;

	len = ft_strlen(key) + ft_strlen(value) + 2;
	str = malloc(len);
	if (!str)
		return (NULL);
	ft_strcpy(str, key);
	ft_strcat(str, "=");
	ft_strcat(str, value);
	return (str);
}

/*
 * Fills an array of strings with environment variables in "key=value" format.
 *   - Only includes nodes with a non-NULL value
 *   - Returns 1 on success, 0 on failure (and frees allocated memory)
 */
static int	fill_envp(char **env_array, t_env *env)
{
	int		i;
	char	*entry;

	i = 0;
	while (env)
	{
		if (env->value)
		{
			entry = join_key_value(env->key, env->value);
			if (!entry)
			{
				while (i-- > 0)
					free(env_array[i]);
				free(env_array);
				return (0);
			}
			env_array[i] = entry;
			i++;
		}
		env = env->next;
	}
	env_array[i] = NULL;
	return (1);
}

/*
 * Converts a linked list of environment variables to an array of strings.
 *   - Only includes variables with a value
 *   - Returns a NULL-terminated array on success, or NULL on failure
 */
char	**env_list_to_array(t_env *env)
{
	int		size;
	char	**env_array;

	size = count_env(env, 1);
	env_array = malloc(sizeof(char *) * (size + 1));
	if (!env_array)
		return (NULL);
	if (!fill_envp(env_array, env))
	{
		free(env_array);
		return (NULL);
	}
	return (env_array);
}
