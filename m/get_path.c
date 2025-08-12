/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dydaniel <dydaniel@student.42sp.org.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 10:12:59 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/05 22:23:13 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_path(t_data_val *data, char *cmd)
{
	char	*path_env;
	char	**splitted_path;
	char	*aux;
	char	*full_path;
	int		i;

	(void)data;
	aux = NULL;
	if (access(cmd, X_OK) == 0)
	{
		full_path = ft_strdup(cmd);
		return (full_path);
	}
	i = 0;
	path_env = getenv("PATH");
	splitted_path = ft_split(path_env, ':');
	while (splitted_path[i])
	{
		aux = ft_strjoin(splitted_path[i], "/");
		full_path = ft_strjoin(aux, cmd);
		free(aux);
		if (access(full_path, X_OK) == 0)
		{
			free_tokens(&splitted_path);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_tokens(&splitted_path);
	return (NULL);
}

void	get_full_path(t_data_val **data)
{
	int	i;

	i = 0;
	if ((*data)->parser)
	{

		(*data)->cmd_path = \
			malloc(sizeof(char *) * ((*data)->num_pipes + 2));
		while (i <= (*data)->num_pipes)
		{
			(*data)->cmd_path[i] = \
				check_path(*data, (*data)->parser[i][0]);
			i++;
		}
	}
	else
	{
		(*data)->cmd_path = malloc(sizeof(char *) * 2);
		(*data)->cmd_path[i] = check_path(*data, (*data)->token[0]);
		i++;
	}
	(*data)->cmd_path[i] = NULL;
}
