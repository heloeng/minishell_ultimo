/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 11:05:52 by helde-so          #+#    #+#             */
/*   Updated: 2025/07/26 11:06:10 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int analize_cd_arguments(t_data_val *d)
{
    char *path;
    
    path = d->token[1];
    if (d->token[2])//muitos argumento 
    {
        ft_putstr_fd("cd: too many arguments\n", 2);
        return 1;
    }
    if (!path || !*path)//cd sem argumento vira HOME
        path = get_env_value("HOME", d->envp);
    return run_cd(path);   
}