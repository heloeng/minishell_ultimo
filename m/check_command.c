/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dydaniel <dydaniel@student.42sp.org.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:58:11 by dydaniel          #+#    #+#             */
/*   Updated: 2025/06/19 14:58:14 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *check_path(char **token, char **envp)
{
    char *path_env;
    char **splitted_path;
    char *aux;
    char *full_path;
    int i;

    i = 0;
    (void)envp;
    path_env = getenv("PATH");//Pega os caminhos
    splitted_path = ft_split(path_env, ':');//Separa cada caminho
    while(splitted_path[i])//Percorre os caminhos
    {
        aux = ft_strjoin(splitted_path[i], "/");
        full_path = ft_strjoin(aux, token[0]);//Adiciona o comando no caminho
        free(aux);
        if (access(full_path, X_OK) == 0)//verifica se é executavel e retorna o caminho
            return (full_path);
        free(full_path);
        i++;
    }
    return (NULL);
}

//Executa o comando, os comentados são o inicio do tratamento do pipe
void exc_command(t_data_val *data)
{
    int i;

    i = 0;
    parse_token(&data);
    if (data->parser)
    {
        while(data->parser[i])
        {
            print_tokens(data->parser[i]);
            i++;
        }
    }
    else
        ft_printf("nao funfou\n");
    i = 0;
    while (data->parser && data->parser[i])
    {
        free_tokens(&data->parser[i]);
        i++;
    }
    if (data->parser)
    {
        free(data->parser);
        data->parser = NULL;
    }
    // if (!data->path)
    // {
    //     free(data->path);
    //     free_tokens(&data->token);
    //     ft_printf("not founded. \n");
    //     return ;
    // }
    // if (data->child_pid == -1)
    // {
    //     perror("Failed to create fork.");
    //     free(data->path);
    //     free_tokens(&data->token);
    //     exit(41);
    // }
    // else if (data->child_pid == 0)
    // {
    //     // dup2(data->fd[1], STDOUT_FILENO);
    //     // close(data->fd[0]);
    //     execve(data->path, data->token, data->envp);
    //     perror("execve failed");
    //     exit(EXIT_FAILURE);
    // }
    // else//AQUI É ONDE PRECISA TRATAR OS PIPES e coisas além
    // {
    //     waitpid(data->child_pid, NULL, 0);
    //     // dup2(data->fd[0], STDIN_FILENO);
    //     // close(data->fd[1]);
    //     // free(data->path);
    //     // data->path = check_path(&data->token[3], data->envp);
    //     // execve(data->path, data->token + 2, data->envp);
    // }
}