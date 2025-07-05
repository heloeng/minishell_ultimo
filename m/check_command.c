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

void handle_command(t_data_val *data)
{
   divide_arguments(&data->token, data->text);
    if (execute_builtin(data))
    {
        free_tokens(&data->token);
        free(data->fd);
        return;
    }
    exc_command(data);
    free_tokens(&data->token);
    free(data->fd); 
}

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
        //excev(token)
}