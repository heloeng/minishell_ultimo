/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:45:21 by helde-so          #+#    #+#             */
/*   Updated: 2025/07/15 17:45:23 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Verifica se existe alguma aspa (simples ou dupla) sem o par de fechamento.
*/
int has_unclosed_quote(char *str) 
{
	char quote;
	
    quote = '\0';
	while (*str)
	{
		if (*str == '\'' || *str == '"')
		{
			if (!quote)
				quote = *str;
			else if (quote == *str)
				quote = '\0';
		}
		str++;
	}
	return (quote != '\0');
}

/*
Continua lendo o input do usuário (com readline("> ")) até que todas as aspas abertas sejam fechadas.
*/
char *complete_unclosed_quote(char *text) 
{
	char *temp;
	char *joined;

	while (has_unclosed_quote(text))
	{
		temp = readline("> ");
		if (!temp)
			break;
		joined = ft_strjoin(text, "\n");
		free(text);
		text = ft_strjoin(joined, temp);
		free(joined);
		free(temp);
	}
	return (text);
}

