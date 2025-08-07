/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_inputs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 19:04:23 by helde-so          #+#    #+#             */
/*   Updated: 2025/07/26 14:12:48 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//guarda o status de saída do último comando executado


int validate_pipe_syntax(const char *input)
{
	if (starts_with_pipe(input))
		return (1);
	if (contains_double_pipe(input))
		return (1);
	if (contains_pipe_space_pipe(input))
		return (1);
	if (ends_with_pipe(input))
		return (1);
	return (0);
}
// Verifica se começa com pipe
int starts_with_pipe(const char *input)
{
	int i;

	i = 0;
	while (ft_isspace(input[i]))
		i++;
	if (input[i] == '|')
	{
		ft_printf("syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}

// Verifica se contém '||' junto
int contains_double_pipe(const char *input)
{
	int i;
	
	i = 0;
	while (input[i])
	{
		if (input[i] == '|' && input[i + 1] == '|')
		{
			if (!char_inside_quotes(input, i)) 
			{
				ft_printf("syntax error near unexpected token `||'\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

// Verifica se contém '|   |' (pipes com espaços entre eles)
int contains_pipe_space_pipe(const char *input)
{
	int i;
	int j;
	
	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
		{
			//Verifica se esse pipe está fora de aspas
			if (!char_inside_quotes(input, i))
			{
				j = i + 1;
				while (ft_isspace(input[j]))
					j++;
				if (input[j] == '|' && !char_inside_quotes(input, j))
				{
					ft_printf("syntax error near unexpected token `|'\n");
					return (1);
				}
			}
		}
		i++;
	}
	return (0);
}
// Verifica se termina com pipe
int ends_with_pipe(const char *input)
{
	int i;
	
	i = ft_strlen(input) - 1;
	while (i >= 0 && ft_isspace(input[i]))
		i--;
	if (i >= 0 && input[i] == '|')
	{
		ft_printf("syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}


