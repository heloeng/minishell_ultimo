/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dydaniel <dydaniel@student.42sp.org.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:12:03 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/14 20:12:38 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_flag_n(const char *arg)
{
	int	j;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	j = 2;
	while (arg[j] == 'n')
		j++;
	return (arg[j] == '\0');
}

int	consume_n_flags(char **args, int *new_line)
{
    int i;

    i = 1;
    *new_line = 1;
    while (args[i] && is_flag_n(args[i]))
    {
        *new_line = 0;
        i++;
    }
    return (i);
}

void ft_echo(t_data_val *data, char **args)
{
    int         i;
    int         new_line;
    const char *scan;

    scan = data->text;
    i = consume_n_flags(args, &new_line);
    while (args[i])
    {
        if (token_was_single_quoted_advance(&scan, args[i]))
            ft_printf("%s", args[i]);
        else
            print_with_expansion(args[i], data);
        if (args[i + 1])
            ft_printf(" ");
        i++;
    }
    if (new_line)
        ft_printf("\n");
}
