/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:34:55 by helde-so          #+#    #+#             */
/*   Updated: 2025/08/12 23:09:40 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void export(char **parser_i, int i, int *status)
{
	ft_putstr_fd("export: ", 2);
	ft_putstr_fd(parser_i[i], 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
	*status = 1;
}

int	ft_export(char **parser_i, t_data_val *data)
{
	int	i;
	int	status;
	char *tmp;

	status = 0;
	i = 1;
	tmp = NULL;
	while(parser_i[i])
	{
		if (!is_valid_identifier(parser_i[i]))
			export(parser_i, i, &status);
		else
		{
			if (!ft_strchr(parser_i[i], '='))
			{
				tmp = ft_strjoin(parser_i[i], "=");
				update_env(&data->envp, tmp);
				free(tmp);
			}
			else
				update_env(&data->envp, parser_i[i]);
		}
		i++;
	}
	return (status);
}
