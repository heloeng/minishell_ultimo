/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_export.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:34:55 by helde-so          #+#    #+#             */
/*   Updated: 2025/06/30 19:34:56 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(char **args, t_data_val *data)
{
    int i;
	int status;

	status = 0;
    i = 1;
    while(args[i])
    {
        if (!is_valid_identifier(args[i]))
		{
			ft_putstr_fd("export: ", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			status = 1;          
		} 
        else
		{
            if (!ft_strchr(args[i], '='))          
            {
                char *tmp = ft_strjoin(args[i], "=");  
                update_env(&data->envp, tmp);
                free(tmp);
            }
            else                                    
                update_env(&data->envp, args[i]);
        }
		     
        i++;
    }
    return (status);
}

