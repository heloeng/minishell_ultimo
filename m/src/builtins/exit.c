/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dydaniel <dydaniel@student.42sp.org.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:06:29 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/11 22:06:32 by dydaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **parser_i)
{
	int	exit_code;

	if (parser_i[2])
	{
		ft_printf("exit\n");
		ft_printf("minishell: exit: too many arguments\n");
		return (1);
	}
	else if (parser_i[1])
	{
		if (ft_isnumeric(parser_i[1]))
		{
			exit_code = ft_atoi_base(parser_i[1], 10);
			exit(exit_code);
		}
		else
		{
			ft_printf("exit\n");
			ft_printf("exit: %s: numeric argument required\n", \
					parser_i[1]);
			exit(255);
		}
	}
	exit(0);
	return (0);
}
