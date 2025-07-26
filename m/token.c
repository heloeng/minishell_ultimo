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
            {
                text++;
                if (*(text + 1) == c && ( *(text + 2) == '"' || *(text + 2) == '\''))
                    text += 3;
            }
            text++;
        }
    }
    return (j);
}

//VERSAO ANTIGA
// //Essa função é chamada quando for encontrado ' ou "
// //independente do que for encontrado é armazenado no char c
// //size = 1 e i = 1 para ja considerar (e pular) a aspa inicial
// int size_of_quote(char c, char *text, int *follow_quote)
// {
//     int size;
//     int i;

//     size = 1;
//     i = 1;
//     while (text[i])
//     {
//         if (text[i + 1] == c && (text[i + 2] == '"' || text[i + 2] == '\''))
//         {
//             c = text[i + 2];
//             i += 2;
//             *follow_quote += 2;
//         }
//         else if (text[i] == c)
//             break;
//         size++;
//         i++;
//     }
//     size++;
//     return (size);
// }


//Essa função é chamada quando for encontrado ' ou "
//independente do que for encontrado é armazenado no char c
//size = 1 e i = 1 para ja considerar (e pular) a aspa inicial
/* token.c */
int	size_of_quote(char quote, char *s, int *follow_quote)
{
	int	i;
    
    i = 1;                     // já estamos em s[0] == quote
	while (s[i] && s[i] != quote)/* avança até encontrar a aspa de fechamento */
		i++;

/*
Versão antiga de size_of_quote()  podia valer 2 quando o
parser “pulava” de aspas simples → duplas (ou vice-versa) dentro do
mesmo token.
Agora percorre o while  contantando até encontrar a aspa de
fechamento original e zera follow_quote.
Portanto, follow_quote será sempre 0 ao sair de size_of_quote().
    */
	*follow_quote = 0;              // não há “pulo extra” agora
	return (i + 1);                 // tamanho inclui a aspa final
}

//!VERSAO ANTIGA
// int size_of_str(char *text)
// {
//     int size;
//     int i;

//     size = 0;
//     i = 0;
//     while (text[i])
//     {
//         if (ft_isspace(text[i]))
//             break;
//         size++;
//         i++;
//     }
//     return (size);
// }

//!NOVA VERSÃO
/*
Antes – size_of_str() parava no primeiro espaço, mesmo que ele
estivesse dentro de aspas → tokens quebrados.
Agora – ele “ignora” espaços enquanto estiver dentro de um par de
aspas, mantendo tudo num token só.
*/
int	size_of_str(char *text)
{
	int i;
	char quote; 

    i = 0;
	quote  = 0; // 0 = fora de aspas
	while (text[i])
	{
		/* se estamos fora de aspas e achamos espaço, fim do token */
		if (!quote && ft_isspace(text[i]))
			break;

		/* abre/fecha bloco de aspas */
		if (text[i] == '\'' || text[i] == '"')
		{
			if (!quote)            // abre aspas
				quote = text[i];
			else if (quote == text[i])
				quote = 0;         // fecha aspas
		}
		i++;
	}
	return (i);                   // tamanho do token
}


//!VERSAO ANTIGA
//Percorre o texto de input e separa por espaços
//Uma divisão feita para palavras (size_of_str)
//Outra divisão feita para aspas (size_of_quote)
// void populate_token(char **token, char *text)
// {
//     int j;
//     int k;
//     int follow_quote;
//     char c;

//     k = 0;
//     follow_quote = 0;
//     while (*text)
//     {
//         if (a_comma(&c, *text))
//             j = size_of_quote(c, text, &follow_quote);// tamanho do token com aspas
//         else if (*text)
//             j = size_of_str(text);// tamanho do token de palavra
//         token[k] = malloc(sizeof(char) * (j + 1));
//         if (!token[k])
//         {
//             ft_printf("failed\n");
//             return ;
//         }
//         if (*text && follow_quote == 0)
//             ft_strlcpy(token[k], text, j + 1);//insere o token no array
//         else 
//             ft_strcpy_quote(token[k], text, j + 1);
//         text += (j + follow_quote);
//         k++;
//         while (ft_isspace(*text))//ignora qualquer espaçamento
//             text++;
//     }
//     token[k] = NULL;
// }
//!nova versao
void populate_token(char **token, char *text)
{
    int j;
    int k;
    int follow_quote;
    char c;

    k = 0;
    follow_quote = 0;
    while (*text)
    {
        if (a_comma(&c, *text))
            j = size_of_quote(c, text, &follow_quote);// tamanho do token com aspas
        else
            j = size_of_str(text);// tamanho do token de palavra
        token[k] = malloc(sizeof(char) * (j + 1));
        if (!token[k])
        {
            ft_printf("failed\n");
            return ;
        }

        if (*text && follow_quote == 0)
            ft_strlcpy(token[k], text, j + 1);//insere o token no array
        else 
            ft_strcpy_quote(token[k], text, j + 1);
        //text += (j + follow_quote); antes
        text += j;  //!ALTEREI AQUI             
        follow_quote = 0;//!ALTEREI AQUI      
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
