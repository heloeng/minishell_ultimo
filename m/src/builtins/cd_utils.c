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
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (token[1] && ft_strncmp(token[1], "-", 2) == 0)
		return (cd_to_oldpwd(data));
	if (!path || !*path)
	{
		path = get_env_value("HOME", data->envp);
		if (!path || !*path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
	}
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
	return (run_cd(data, path));
}


void	update_pwd(t_data_val *data, const char *oldpwd, char *cwd, size_t n)
{
	char	*key_value;

	key_value = ft_strjoin("OLDPWD=", oldpwd);
	if (key_value)
	{
		update_env(&data->envp, key_value);
		free(key_value);
	}
	if (getcwd(cwd, n))
	{
		key_value = ft_strjoin("PWD=", cwd);
		if (key_value)
		{
			update_env(&data->envp, key_value);
			free(key_value);
		}
	}
}

int	cd_to_oldpwd(t_data_val *data)
{
	char	*old;

	old = get_env_value("OLDPWD", data->envp);
	if (!old || !*old)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		g_exit_status = 1;
		return (1);
	}
	if (run_cd(data, old) != 0)
		return (1);
	ft_printf("%s\n", get_env_value("PWD", data->envp));
	return (0);
}

