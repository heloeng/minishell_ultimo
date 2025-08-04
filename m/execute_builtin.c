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

int execute_builtin(t_data_val *data) //identifica se é um builtin e executa ele se for.
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
        // analize_cd_arguments(data);
        g_exit_status = analize_cd_arguments(data);
        return (1);
    }
    if (ft_strncmp(data->token[0], "unset", 5) == 0)
    {
        ft_unset_args(data->token, data); // executa unset para todos os args
        return (1); 
    }
    if (ft_strncmp(data->token[0], "export", 6) == 0)
		// return (ft_export(data->token, data));
		g_exit_status = ft_export(data->token, data);
        return (1);
    return (0);// não é builtin
    
}

//mensagem de permissão
int ft_exit(t_data_val *data)
{
    int exit_code;

    if (data->token[2])
    {
        ft_printf("exit\n");
        ft_printf("minishell: exit: too many arguments\n");
        return (1);
    }
    else if (data->token[1])
    {
        if (ft_isnumeric(data->token[1]))
        {
            exit_code = ft_atoi_base(data->token[1], 10);
            exit(exit_code);
        }
        else
        {
            ft_printf("exit\n");
            ft_printf("exit: %s: numeric argument required\n", data->token[1]);
            exit(255);
        }
    }
    exit(0);
    return (0);
}

void ft_pwd(t_data_val *data)
{
    char cwd[1024];
    (void)data;
    if(getcwd(cwd, sizeof(cwd)) == NULL)
    {
        ft_printf("pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
        return;
    }
    ft_putstr_fd(cwd, 1);
    ft_putstr_fd("\n", 1);
}

// há outro erro de permissão denied
void ft_env(t_data_val *data)
{
    int i;

    if(data->token[1])
    {
        ft_printf("env: %s: No such file or directory\n", data->token[1]);
        return ;
    }
    i = 0;
    while(data->envp[i])
    {
        ft_printf("%s\n", data->envp[i]);
        i++;
    }
}

/*

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
*/

/*
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
*/


//falta validações
char *get_env_value(char *name, char **envp)
{
	int     i;
	size_t  len;

	len = ft_strlen(name);//calcula o tamanho da variavel
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, len) && envp[i][len] == '=')
			return (envp[i] + len + 1); // pula o "NAME=" e retorna valor
		i++;
	}
	return (""); //retorna string vazia se não encontrar
}





