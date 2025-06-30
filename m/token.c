/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dydaniel <dydaniel@student.42sp.org.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:05:47 by dydaniel          #+#    #+#             */
/*   Updated: 2025/06/16 21:05:50 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int num_tokens(char *text)
{
    int j;
    char c;

    j = 0;
    while (*text)
    {
        while (*text && ft_isspace(*text))
            text++;
        if (*text && !ft_isspace(*text) && *text != '\n')
            j++;
        if (*text != '\'' && *text != '"')
        {
                while (*text && !ft_isspace(*text) && *text != '\n')
                    text++;
        }
        else
        {
            c = *text;
            text++;
            while (*text && *text != c && *text != '\n')
                text++;
            text++;
        }        
    }
    return (j);
}

//Essa função é chamada quando for encontrado ' ou "
//independente do que for encontrado é armazenado no char c
//size = 1 e i = 1 para ja considerar (e pular) a aspa inicial
int size_of_quote(char c, char *text)
{
    int size;
    int i;

    size = 1;
    i = 1;
    while (text[i])
    {
        if (text[i] == c)
            break;
        size++;
        i++;
    }
    size++;
    return (size);
}

int size_of_str(char *text)
{
    int size;
    int i;

    size = 0;
    i = 0;
    while (text[i])
    {
        if (ft_isspace(text[i]))
            break;
        size++;
        i++;
    }
    return (size);
}

//Percorre o texto de input e separa por espaços
//Uma divisão feita para palavras (size_of_str)
//Outra divisão feita para aspas (size_of_quote)
void populate_token(char **token, char *text)
{
    int j;
    int k;
    char c;

    k = 0;
    while (*text)
    {
        if (a_comma(&c, *text))
            j = size_of_quote(c, text);// tamanho do token com aspas
        else if (*text)
            j = size_of_str(text);// tamanho do token de palavra
        token[k] = malloc(sizeof(char) * (j + 1));
        if (!token[k])
        {
            ft_printf("failed\n");
            return ;
        }
        if (*text)
            ft_strlcpy(token[k], text, j + 1);//insere o token no array
        text += j;
        k++;
        while (ft_isspace(*text))//ignora qualquer espaçamento
            text++;
    }
    token[k] = NULL;
}

void divide_arguments(char ***token, char *text)
{
    int i;

    i = num_tokens(text);
    *token = malloc(sizeof(char *) * (i + 1));
    if(!(*token))
        return ;// //if malloc falhar, free e libera o resto
    populate_token(*token, text);
}

void free_tokens(char ***token)
{
    int i;

    i = 0;
    while ((*token)[i])
    {
        free((*token)[i]);
        i++;
    }
    free(*token);
}
