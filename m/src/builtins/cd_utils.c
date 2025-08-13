/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 11:05:52 by helde-so          #+#    #+#             */
/*   Updated: 2025/08/12 22:32:36 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	analize_cd_arguments(t_data_val *data, char **token)
{
	char	*path;
	char	*val;

	path = token[1];
	if (token[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	if (!path || !*path)
		path = get_env_value("HOME", data->envp);
	if (path && path[0] == '$')
	{
		val = get_env_value(path + 1, data->envp);
		if (!val || !*val)
		{
			ft_putstr_fd("cd: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (1);
		}
		path = val;
	}
	return (run_cd(path));
}
