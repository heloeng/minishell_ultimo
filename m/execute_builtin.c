/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:35:13 by helde-so          #+#    #+#             */
/*   Updated: 2025/08/11 22:07:47 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin(char *cmd)
{
	int	flag_builtin;

	flag_builtin = NO_BUILTIN;
	if (!ft_strcmp(cmd, "cd"))
		flag_builtin = CD;
	else if (!ft_strcmp(cmd, "echo"))
		flag_builtin = ECHO;
	else if (!ft_strcmp(cmd, "export"))
		flag_builtin = EXPORT;
	else if (!ft_strcmp(cmd, "pwd"))
		flag_builtin = PWD;
	else if (!ft_strcmp(cmd, "env"))
		flag_builtin = ENV;
	else if (!ft_strcmp(cmd, "unset"))
		flag_builtin = UNSET;
	else if (!ft_strcmp(cmd, "exit"))
		flag_builtin = EXIT;
	return (flag_builtin);
}

int	builtin_pack_1(t_data_val *data, char **token, int flag)
{
	if (flag == PWD)
	{
		ft_pwd();
		g_exit_status = 0;
		return (1);
	}
	if (flag == ENV)
	{
		ft_env(data, token);
		g_exit_status = data->last_exit;
		return (1);
	}
	if (flag == ECHO)
	{
		ft_echo(data, token);
		g_exit_status = 0;
		return (1);
	}
	if (flag == CD)
	{
		g_exit_status = analize_cd_arguments(data, token);
		return (1);
	}
	return (0);
}

int	builtin_pack_2(t_data_val *data, char **token, int flag)
{
	if (flag == UNSET)
	{
		ft_unset_args(token, data);
		g_exit_status = 0;
		return (1);
	}
	if (flag == EXPORT)
	{
		g_exit_status = ft_export(token, data);
		return (1);
	}
	return (0);
}

int	execute_builtin(t_data_val *data, char **token)
{
	int	flag;

	flag = check_builtin(token[0]);
	if (flag == EXIT)
		return (ft_exit(token));
	if (flag == NO_BUILTIN)
		return (0);
	else if (builtin_pack_1(data, token, flag) || \
			builtin_pack_2(data, token, flag))
		return (1);
	return (0);
}
