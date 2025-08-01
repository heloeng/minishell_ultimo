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
imprime uma string com possível expansão de variáveis ($VAR) 
e do código de saída ($?)
É chamada apenas quando o conteúdo está dentro de aspas duplas ("), 
porque aspas simples são tratadas em print_single_quoted.
*/
void print_with_expansion(char *str, char **envp)
{
	int i;//índice para percorrer str.
	int inc;  //quantas posições i deve avançar após processar um $.
	char *exit_str; //string que conterá o valor convertido de g_exit_status via ft_itoa.

	//Verifica se a string inteira é exatamente "$?" (com \0 no final), ou seja, echo "$?".
	// Caso especial: "$?" sozinho
	// if(ft_strncmp(str, "$?", 3) == 0)//Se for "$?": echo $? ou echo "$?"
	if (ft_strncmp(str, "$?", 2) == 0 && str[2] == '\0')
	{
		exit_str = ft_itoa(g_exit_status);//Converte g_exit_status para string.
		ft_printf("%s", exit_str);//Imprime.
		free(exit_str);//Libera a memória.
		return;//Sai da função, pois nada mais precisa ser impresso.
	}

	//Começa a percorrer a string caractere por caractere até o fim (\0).
	i = 0;
	while (str[i])
	{
		inc = 1;//Por padrão, o índice vai andar 1 caractere por vez (caso não encontre $).
		// Só expande se for '$' fora de aspas simples : echo $USER ou echo "User: $USER"
		if (str[i] == '$' && !char_inside_quotes(str, i))
			inc = handle_dollar_expansion(str + i, envp);//Chama handle_dollar_expansion, que imprime o valor da variável (se existir).
		else// Se não for $, imprime o caractere atual como está (normal).
			ft_putchar_fd(str[i], 1);
		i += inc;//Avança o índice conforme o valor de inc.
	}
}

//analise a variavel iniciada com $ dentro da string e imprime seu valor (print_expanded_var)
int handle_dollar_expansion(char *str, char **envp)
{
	int len;
	char *var_name;
	char *exit_str; //string que conterá o valor convertido de g_exit_status via ft_itoa.
	
	if (str[1] == '?')  // caso especial para $?
	{
		exit_str = ft_itoa(g_exit_status); // converte código de saída
		ft_printf("%s", exit_str);               // imprime o valor
		free(exit_str);                          // libera memória
		return (2);                              // pula "$?"
	}
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

char *remove_all_quotes(const char *token)
{
	int i;
	int j;
	char *result;

	i = 0,
	j = 0;
	
	result = malloc(ft_strlen(token) + 1);
	if (!result)
		return (NULL); 
	// Percorre o token original caractere por caractere
	while (token[i])
	{
		// Se o caractere atual NÃO for uma aspa simples ou dupla
		if (token[i] != '\'' && token[i] != '"')
			result[j++] = token[i]; // Copia para a nova string
		// Se for uma aspa, apenas ignora (não copia)
		i++;
	}
	result[j] = '\0';
	return result;
}


