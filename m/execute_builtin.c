/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:35:13 by helde-so          #+#    #+#             */
/*   Updated: 2025/07/05 19:37:11 by helde-so         ###   ########.fr       */
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
        analize_cd_arguments(data);
        return (1);
    }
    if (ft_strncmp(data->token[0], "export", 6) == 0)
		return (ft_export(data->token, data));
    return (0);
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

void ft_echo(t_data_val *data)
{
	int i;
	int new_line;

	i = 1;
	new_line = 1;
	while (data->token[i] && ft_strncmp(data->token[i], "-n", 3) == 0)
	{
		new_line = 0;
		i++;
	}
	while (data->token[i])
	{
        if (data->token[i][0] == '\'' && data->token[i][ft_strlen(data->token[i]) - 1] == '\'')
			print_single_quoted(data->token[i]);//trata tokens entre aspas simples (')
		else if (data->token[i][0] == '"' && data->token[i][ft_strlen(data->token[i]) - 1] == '"')
            print_double_quoted(data->token[i], data->envp);//trata tokens entre aspas duplas (")
		else if (ft_strchr(data->token[i], '$'))// Caso: variável fora de aspas
			print_with_expansion(data->token[i], data->envp);
		else
			ft_printf("%s", data->token[i]); // Caso: texto simples, sem aspas ou $
		if (data->token[i + 1]) ft_printf(" ");
		i++;
	}
	if (new_line)
		ft_printf("\n");
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
    char cwd[1024];
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


//função teste
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





