/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dydaniel <dydaniel@student.42sp.org.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:08:15 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/11 22:08:18 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(t_data_val *data, char **token)
{
	int	i;

	i = 0;
	if (token[1])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(token[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		data->last_exit = 127;
		return ;
	}
	while (data->envp[i])
	{
		ft_printf("%s\n", data->envp[i]);
		i++;
	}
	data->last_exit = 0;
}

char	*get_env_value(char *name, char **envp)
{
	int	i;
	size_t	len;


	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, len) && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return ("");
}