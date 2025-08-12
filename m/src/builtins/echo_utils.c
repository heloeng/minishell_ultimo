/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:44:50 by helde-so          #+#    #+#             */
/*   Updated: 2025/07/26 13:59:01 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void expand_loop(char *str, t_data_val *data)
{
    int i;
    int inc;

    i = 0;
    while (str[i])
    {
        if (str[i] == '\\' && str[i + 1] == '$')
        {
            ft_putchar_fd('$', 1);
            i += 2;
            continue;
        }
        if (str[i] == '$')
        {
            inc = handle_dollar_expansion(str + i, data);
            i += inc;
        }
        else
        {
            ft_putchar_fd(str[i], 1);
            i++;
        }
    }
}

void print_with_expansion(char *str, t_data_val *data)
{
    char *exit_str;

    if (str[0] == '$' && str[1] == '?' && str[2] == '\0')
    {
        exit_str = ft_itoa(data->last_exit);
        ft_printf("%s", exit_str);
        free(exit_str);
        return;
    }
    expand_loop(str, data);
}

int  handle_dollar_expansion(char *str, t_data_val *data)
{
	int len;
	char *var_name;
	char *exit_str; 
	
	if (str[1] == '?')  
	{
		exit_str = ft_itoa(data->last_exit); 
		ft_printf("%s", exit_str);               
		free(exit_str);                         
		return (2);                            
	}
	len = 0;
	while (str[1 + len] && (ft_isalnum(str[1 + len]) || str[1 + len] == '_'))
		len++;
	if (len > 0)
	{
		var_name = ft_substr(str, 1, len);
		if (!var_name)
			return (len + 1);
		print_expanded_var(var_name, data->envp);
		free(var_name);
		return (len + 1);
	}
	ft_putchar_fd('$', 1);
	return (1);
}

void print_expanded_var(char *var_name, char **envp)
{
	char *value;

	value = get_env_value(var_name, envp);
	ft_printf("%s", value);
}

// Retorna 1 se a PRÓXIMA ocorrência de `token` a partir de *cursor
// estiver cercada por aspas simples; move *cursor para depois do token.
int token_was_single_quoted_advance(const char **cursor, const char *token)
{
    const char *p;
    size_t      len;

    if (!cursor || !*cursor || !token)
        return 0;

    len = ft_strlen(token);
    p = ft_strnstr(*cursor, token, ft_strlen(*cursor));
    if (!p)
        return 0;
    if (p > *cursor && *(p - 1) == '\'' && *(p + len) == '\'')
    {
        *cursor = p + len;
        return 1;
    }
    *cursor = p + len;
    return 0;
}

