/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:35:06 by helde-so          #+#    #+#             */
/*   Updated: 2025/08/12 23:13:58 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**build_new_env(char **old, const char *name)
{
	char	**new;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = ft_strlen(name);
	while (old[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return NULL;
	i = 0;
	while(old[i])
	{
		if(!(ft_strncmp(old[i], name, len) == 0 && old[i][len] == '='))
			new[j++] = ft_strdup(old[i]);
		i++;
	}
	new[j] = NULL;
	return (new);
}

void	ft_unset(char ***envp, char *name)
{
	char	**old;
	char	**new;

	if (!envp || !*envp || !name)
		return;
	old = *envp;
	new = build_new_env(old, name);
	if (!new)
		return;
	free(old);
	*envp = new;
}

int	ft_unset_args(char **parser_i, t_data_val *data)
{
	int i;

	i = 1;
	while (parser_i[i])
	{
		ft_unset(&data->envp, parser_i[i]);
		i++;
	}
	return (0);
}
