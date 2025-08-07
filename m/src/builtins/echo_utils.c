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

void print_double_quoted(char *token, t_data_val *data)
{
	char *trimmed;
	int len;

	len = ft_strlen(token);
	trimmed = malloc(sizeof(char) * (len - 2 + 1));
	if (!trimmed)
		return;
	ft_strlcpy(trimmed, token + 1, len - 1);
	print_with_expansion(trimmed, data);
	free(trimmed);
}

void print_with_expansion(char *str, t_data_val *data)
{
	int i;
	int inc;  
	char *exit_str; 
	
	if (ft_strncmp(str, "$?", 2) == 0 && str[2] == '\0')
	{
		exit_str = ft_itoa(data->last_exit);
		ft_printf("%s", exit_str);
		free(exit_str);
		return;
	}

	i = 0;
	while (str[i])
	{
		inc = 1;
		
		if (str[i] == '$' && !char_inside_quotes(str, i))
			inc = handle_dollar_expansion(str + i, data);
		else
			ft_putchar_fd(str[i], 1);
		i += inc;
	}
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
	while (token[i])
	{
		if (token[i] != '\'' && token[i] != '"')
			result[j++] = token[i]; 
		i++;
	}
	result[j] = '\0';
	return result;
}

int	was_single_quoted(const char *cmdline, const char *token)
{
	const char	*p;
	size_t		len;

	p = cmdline;
    len = ft_strlen(token);
	while ((p = ft_strnstr(p, token, ft_strlen(p))))
	{
		if (p > cmdline && *(p - 1) == '\''         
			&& *(p + len) == '\'')                   
			return (1);
		p += len;                                 
	}
	return (0);
}

char *get_env_value(char *name, char **envp)
{
	int     i;
	size_t  len;

	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, len) && envp[i][len] == '=')
			return (envp[i] + len + 1); 
		i++;
	}
	return (""); 
}