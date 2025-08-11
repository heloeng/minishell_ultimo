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


void print_with_expansion(char *str, t_data_val *data)
{
    int i;
    
    if (ft_strncmp(str, "$?", 2) == 0 && str[2] == '\0')
    {
        char *exit_str = ft_itoa(data->last_exit);
        ft_printf("%s", exit_str);
        free(exit_str);
        return;
    }

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
            int consumed = handle_dollar_expansion(str + i, data);
            if (consumed <= 0) consumed = 1;  
            i += consumed;
            continue;
        }
        ft_putchar_fd(str[i], 1);
        i++;
    }
}

int handle_dollar_expansion(char *str, t_data_val *data)
{
    int len;

    if (str[1] == '?')
    {
        char *exit_str = ft_itoa(data->last_exit);
        ft_printf("%s", exit_str);
        free(exit_str);
        return 2;
    }
    len = 0;
    while (str[1 + len] && (ft_isalnum((unsigned char)str[1 + len]) || str[1 + len] == '_'))
    {
        if (len >= 255) break;
        len++;
    }

    if (len > 0)
    {
        char name[256];
        int j;
        for (j = 0; j < len && j < 255; j++)
            name[j] = str[1 + j];
        name[j] = '\0';
        char *val = get_env_value(name, data->envp);
        ft_printf("%s", val);

        return len + 1; 
    }
    ft_putchar_fd('$', 1);
    return 1;
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
