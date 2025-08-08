/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:35:13 by helde-so          #+#    #+#             */
/*   Updated: 2025/07/26 12:04:51 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_builtin(t_data_val *data) 
{
    char **args = data->token;
    int i;

    i = 0;
    while (args[i] && ft_strchr(args[i], '='))
        i++;
    if (!args[i])
        return (0);
    if(ft_strncmp(data->token[0], "exit", 5) == 0)
        return (ft_exit(data));
    if(ft_strncmp(data->token[0], "pwd", 4) == 0)
    {
        ft_pwd(data);
        return (1); 
    }
     if(ft_strncmp(data->token[0], "env", 3) == 0)
    {
        ft_env(data);
        return (1);
    }
    if (ft_strncmp(data->token[0], "echo", 4) == 0)
    {
        ft_echo(data);
        return (1);
    }
    if(ft_strncmp(data->token[0], "cd", 2) == 0)
    {
        data->last_exit = analize_cd_arguments(data);
        return (1);
    }
    if (ft_strncmp(data->token[0], "unset", 5) == 0)
    {
        ft_unset_args(data->token, data); 
        return (1); 
    }
    if (ft_strncmp(data->token[0], "export", 6) == 0)
		data->last_exit = ft_export(data->token, data);
        return (1);
    return (0);// não é builtin
    
}


// há outro erro de permissão denied
void ft_env(t_data_val *data)
{
    int i;

    if (data->token[1])
    {
        ft_putstr_fd("env: ", 2);
        ft_putstr_fd(data->token[1], 2);
        ft_putstr_fd(": No such file or directory\n", 2);
        data->last_exit = 127;         
        return;
    }
    i = 0;
    while (data->envp[i])
    {
        ft_printf("%s\n", data->envp[i]);
        i++;
    }
    data->last_exit = 0;             
}






