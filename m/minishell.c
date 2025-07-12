/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:54:54 by dydaniel          #+#    #+#             */
/*   Updated: 2025/06/30 15:25:17 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"  

void print_tokens(char **token)
{
    int i;

    i = 0;
    while(token[i])
    {
        printf("token %i: %s\n", i, token[i]);
        i++;
    }
}

char *get_envp_path(char **envp)
{
    char *envp_path;
    int i;

    envp_path = NULL;
    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PATH", 4) == 0)
        {
            envp_path = ft_strdup(envp[i]);
        }
        i++;
    }
    return (envp_path);
}


int a_comma(char *c, char c_text)
{
    if (c_text == '"' || c_text == '\'')
    {
        *c = c_text;
        return (1);
    }
    else
        return (0);
}

void recive_inputs(t_data_val *data)
{
    while (1) 
    {
        data->text = readline("abc>>");  
        if (data->text == NULL)
        {
            write(STDOUT_FILENO, "exit\n", 5);
            break;
        }
        data->text = complete_unclosed_quote(data->text);//INSERI ESSA LINHA
        if (data->text != NULL &&  num_tokens(data->text) > 0)
            add_history(data->text);
        if (strcmp(data->text, "exit") == 0)  
        {
            rl_clear_history();
            free(data->text);
            break;       
        }
        handle_command(data);
        free(data->text);
    }
}


/*! dividi a função para chamar a função que executa os builtins

void recive_inputs(t_data_val *data)
{
    int i;
    while (1) 
    {
        i = 0;
        data->text = readline("abc>>");  
        if (data->text == NULL)
        {
            write(STDOUT_FILENO, "exit\n", 5);
            break;
        }
        if (data->text != NULL &&  num_tokens(data->text) > 0)
            add_history(data->text);
        if (strcmp(data->text, "exit") == 0)  
        {
            rl_clear_history();
            free(data->text);
            break;       
        }
        divide_arguments(&data->token, data->text);// faz a tokenização-- retirei
        exc_command(data);// executa o comando -- retirei
        free(data->text);
        free_tokens(&data->token);//- retirei
        free(data->fd);//- retirei
    }
}

*/

//inicia e atribui valores da estrutura para enviar para 
//o resto do programa
void init_data(t_data_val **data, char **envp)
{
    (*data)->envp = envp;
    (*data)->fd = NULL;
    (*data)->text = NULL;
    (*data)->token = NULL;
    (*data)->child_pid = 0;
    (*data)->parser = NULL;
    (*data)->envp_path = get_envp_path(envp);
    (*data)->num_pipes = 0;
}

int main(int argc, char **argv, char **envp)
{
    t_data_val *data;

    (void)argc;  
    (void)argv;
    data = malloc(sizeof(t_data_val));
    if (!data)
        return (0);
    init_data(&data, envp);//inicia a estrutura  
    configure_signal();
    recive_inputs(data);
    return (0); 
}
