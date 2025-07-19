/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dydaniel <dydaniel@student.42sp.org.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 10:14:17 by dydaniel          #+#    #+#             */
/*   Updated: 2025/06/28 10:14:22 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_pipes(char **token)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (token[i])
    {
        if (token[i][0] == '|')
            j++;
        i++;
    }
    return (j);
}

char **cmd_arg(char **token, int *j)
{
    char **parsed;
    int num_arg;
    int i;

    num_arg = 0;
    i = 0;
    while (token[*j + num_arg] && token[*j + num_arg][0] != '|')
        num_arg++;
    parsed = malloc(sizeof(char *) * (num_arg + 1));
    if (!parsed)
        return NULL;
    while (token[*j] && token[*j][0] != '|')
    {
        parsed[i] = ft_strdup(token[(*j)]);
        (*j)++;
        i++;
    }
    (*j)++;
    parsed[i] = NULL;
    return (parsed);
}

void create_fds(t_data_val **data, int num_pipes)
{
    int i;

    i = 0;
    (*data)->fd = malloc(sizeof(int *) * (num_pipes + 1));
    while (i < num_pipes)
    {
        (*data)->fd[i] = malloc(sizeof(int) * 2);
        if (pipe((*data)->fd[i]) < 0)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    (*data)->fd[i] = NULL;
}

void parse_token(t_data_val **data)
{
    int num_pipes;
    int i;
    int j;

    i = 0;
    j = 0;
    num_pipes = check_pipes((*data)->token);
    (*data)->num_pipes = num_pipes;
    if (num_pipes > 0)
    {
        create_fds(data, num_pipes);
        (*data)->parser = malloc(sizeof(char ***) * (num_pipes + 2));
        if ((*data)->parser == NULL)
            return ;
        while (i <= num_pipes)
        {
            (*data)->parser[i] = cmd_arg((*data)->token, &j);
            i++;
        }
        (*data)->parser[i] = NULL;
    }
    else
        return ;
}

void free_parser(t_data_val *data)
{
    int i;

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
}