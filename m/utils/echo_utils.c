/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:44:50 by helde-so          #+#    #+#             */
/*   Updated: 2025/07/15 17:44:55 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
trata tokens entre aspas simples (')
Remove as aspas simples do início e do fim
Imprime o conteúdo, sem expandir variáveis
*/
void print_single_quoted(char *token)
{
	char *trimmed;
	int len;

	len = ft_strlen(token);
	trimmed = malloc(sizeof(char) * (len - 2 + 1));
	if (!trimmed)
		return;
	ft_strlcpy(trimmed, token + 1, len - 1);
	ft_printf("%s", trimmed);
	free(trimmed);
}


/*
trata tokens entre aspas duplas (")
Remove as aspas duplas do início e do fim
Chama a função print_with_expansion() para expandir as variáveis
*/
void print_double_quoted(char *token, char **envp)
{
	char *trimmed;
	int len;

	len = ft_strlen(token);
	trimmed = malloc(sizeof(char) * (len - 2 + 1));
	if (!trimmed)
		return;
	ft_strlcpy(trimmed, token + 1, len - 1);
	print_with_expansion(trimmed, envp);
	free(trimmed);
}

/*
percorre a string e expande a variavel iniciada com $
*/
void print_with_expansion(char *str, char **envp)
{
	int i;
	int inc;

	i = 0;
	while (str[i])
	{
		inc = 1;
		if (str[i] == '$')
			inc = handle_dollar_expansion(str + i, envp);
		else
			ft_putchar_fd(str[i], 1);
		i += inc;
	}
}

//analise a variavel iniciada com $ dentro da string e imprime seu valor (print_expanded_var)
int handle_dollar_expansion(char *str, char **envp)
{
	int len;
	char *var_name;

	len = 0;
	while (str[1 + len] && (ft_isalnum(str[1 + len]) || str[1 + len] == '_'))
		len++;
	if (len > 0)
	{
		var_name = ft_substr(str, 1, len);
		if (!var_name)
			return (len + 1);
		print_expanded_var(var_name, envp);
		free(var_name);
		return (len + 1);
	}
	ft_putchar_fd('$', 1);
	return (1);
}

/*
Imprimir o valor de uma variável de ambiente passada
*/
void print_expanded_var(char *var_name, char **envp)
{
	char *value;

	value = get_env_value(var_name, envp);
	ft_printf("%s", value);
}




