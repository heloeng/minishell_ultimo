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

/*FUNÇAO ANTERIOR
int	ft_exit(char **parser_i)
{
	int	exit_code;

	if (parser_i[2])
	{
		perror("too many arguments");
		exit(1);
	}
	else if (parser_i[1])
	{
		exit_code = ft_atoi_base(parser_i[1], 10);
		if (exit_code > 0)
			exit(exit_code);
		else if (exit_code < 0)
			exit(156);
		else
		{
			perror("numeric argument required");
			exit(2);
		}
	}
	exit(1);
	return (0);
}
*/

int	ft_exit(char **args)
{
	long	val;

	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_exit_status = 1;
		return (1);
	}
	if (args[1])
	{
		if (!ft_isnumeric_1(args[1])) 
		{
			ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
			exit(2);
		}
		val = ft_atoi_base(args[1], 10);
		exit((unsigned char)val);
	}
	exit(g_exit_status);
}
