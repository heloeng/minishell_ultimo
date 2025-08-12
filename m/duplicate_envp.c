/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dydaniel <dydaniel@student.42sp.org.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:29:59 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/11 21:30:02 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **duplicate_envp(char **envp)
{
	int count = 0;
	int i = 0;
	char **new_env;

	while (envp[count])
		count++;

	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return NULL;

	while (i < count)
	{
		new_env[i] = ft_strdup(envp[i]);
		i++;
	}
	new_env[i] = NULL;
	return new_env;
}
