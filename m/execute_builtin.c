/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:35:13 by helde-so          #+#    #+#             */
/*   Updated: 2025/06/30 19:35:15 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_builtin(t_data_val *data) //identifica se é um builtin e executa ele se for.
{
    char **args = data->token;
    int i;

    i = 0;
    while (args[i] && ft_strchr(args[i], '='))
    {
        i++;
    }
    if (!args[i])
        return (0);
    
    if(ft_strncmp(data->token[0], "exit", 5) == 0)
    {
        return (ft_exit(data)); 
    }
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
        analize_cd_arguments(data);
        return (1);
    }
    if (ft_strncmp(data->token[0], "export", 6) == 0)
    {
		return (ft_export(data->token, data));
    }
    return (0); // não era builtin  shell deve seguir com execve()
}


int ft_exit(t_data_val *data)
{
    int exit_code;

    ft_printf("exit\n");
    if (data->token[2])
    {
        ft_printf("minishell: exit: too many arguments\n");
        return (1); // erro, mas não sai
    }
    else if (data->token[1])//Verifica primeiro se o argumento existe (data->token[1])
    {
        if (ft_isnumeric(data->token[1]))//Depois, verifica se ele é numérico
        {
            exit_code = ft_atoi_base(data->token[1], 10);//ft_atoi_base() exige dois argumentos:  precisa dizer qual base numérica usar — e no caso de exit, é sempre base 10.
            exit(exit_code);
        }
        else
        {
            ft_printf("minishell: exit: %s: numeric argument required\n", data->token[1]);
            exit(255);
        }
    }
    exit(0); // sem argumentos → exit 0
    return (0); // nunca chega aqui, mas para evitar warning
}

void ft_pwd(t_data_val *data)//Mostra o diretório atual do shell
{
    char cwd[PATH_MAX];
    (void)data;
if(getcwd(cwd, sizeof(cwd)) == NULL)
{
    ft_printf("pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
    return;
}
   ft_putstr_fd(cwd, 1);
   ft_putstr_fd("\n", 1);
}

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

void ft_echo(t_data_val *data)
{
    char **args = data->token;
    int newline;
    int i;

    i = 1;
    newline = 1; 
    while(args[i] && is_n_flag(args[i]))
    {
        newline = 0; 
        i++;
    }
    while (args[i])
    {
        char *s = args[i];
        int   j = 0;

        while (s[j])
        {
            if (s[j] != '"' && s[j] != '\'')
                ft_printf("%c", s[j]);
            j++;
        }

        if (args[i + 1])
            ft_printf(" ");
        i++;
    }
    if(newline)
    {
        ft_printf("\n");
    }
}

int is_n_flag(const char *str) // Verifica se o argumento é uma flag do tipo "-n", "-nn", "-nnn"...
{
    int i; 
    
    i = 1; 
    if (str[0] != '-') /
        return (0);

    if (str[1] == '\0') 
        return (0);

    while (str[i]) 
    {
        if (str[i] != 'n') 
            return (0);
        i++; 
    }
    return (1);
}

int analize_cd_arguments(t_data_val *data)
{
    char *path;

    path = NULL;
    if(data->token[1] == NULL) 
    {
        path = getenv("HOME");
        return (run_cd(path));
    }
    if (ft_strncmp(data->token[1], "-", 2) == 0)// cd -
    {
        path = getenv("OLDPWD");
        if (!path)
        {
            ft_printf("cd: OLDPWD not set\n");
            return (1);
        }
    ft_printf("%s\n", path);
    return (run_cd(path));
    }
    if(data->token[1][0] == '~')//cd ~ ou ~/Documentos - data->token[1][0]
    {
        path = getenv("HOME");
        return (run_cd(path));
    }
    return (run_cd(data->token[1]));
}

int run_cd(char *path)
{
    char cwd[PATH_MAX];
    char *oldpwd;
   
    oldpwd = getcwd(NULL, 0);// aloca dinamicamente o espaço necessário pra armazenar o caminho atual.
    {
        perror("cd");
        return (1);
    }
    if(chdir(path) != 0)//chdir() altera o diretório atual do processo para o caminho passado em path.
    {
        perror("cd");
        free(oldpwd);
        return (1);
    }

    setenv( "OLDPWD", oldpwd, 1); // coloca o diretorio anterior
    free(oldpwd);
    getcwd(cwd, sizeof(cwd));  // cwd já está declarado no topo Obter novo diretório atual
    setenv( "PWD", cwd, 1); // / coloca o novo diretório atual
    return (0);
}

