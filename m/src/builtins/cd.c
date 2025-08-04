/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 11:07:39 by helde-so          #+#    #+#             */
/*   Updated: 2025/07/26 11:08:05 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int run_cd(char *path)
{
    char cwd[1024];
    char *oldpwd;
   
    oldpwd = getcwd(NULL, 0);
    if (!oldpwd)                       
    {
        perror("cd");
        return 1;
    }

    if (chdir(path) == -1)             
    {
        perror("cd");                   
        free(oldpwd);
        return 1;
    }

    //atualiza OLDPWD e PWD 
    setenv("OLDPWD", oldpwd, 1);
    free(oldpwd);

    if (getcwd(cwd, sizeof(cwd)))
        setenv("PWD", cwd, 1);

    return 0;                            
}