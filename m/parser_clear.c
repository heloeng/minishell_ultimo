/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dydaniel <dydaniel@student.42sp.org.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 20:53:14 by dydaniel          #+#    #+#             */
/*   Updated: 2025/07/29 20:53:17 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"


void args_to_clear(char **parser, int *args, int i)
{
    while(parser[i])
    {
        if (parser[i][0] == '>' || parser[i][0] == '<')
            i += 2;
        else
        {
            i++;
            (*args)++;
        }
    }
}


char **clear_parser(char **parser)
{
    int i;
    int args;
    char **cleaned;

    i = 0;
    args = 0;
    args_to_clear(parser, &args, i);
    cleaned = malloc(sizeof(char *) * (args + 1));
    args = 0;
    while (parser[i])
    {
        if (parser[i][0] == '>' || parser[i][0] == '<')
            i += 2;
        else
        {
            cleaned[args] = ft_strdup(parser[i]);
            args++;
            i++;
        }
    }
    cleaned[args] = NULL;
    free_tokens(&parser);
    return (cleaned);
}
