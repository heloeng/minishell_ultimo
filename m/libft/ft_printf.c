/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:48:45 by helde-so          #+#    #+#             */
/*   Updated: 2025/08/15 21:43:29 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_char(char c)
{
	return (write(1, &c, 1));
}

int	print_string(char *str)
{
	int	count;

	count = 0;
	if (str == NULL)
		return (print_string("(null)"));
	while (str[count] != '\0')
		count += print_char(str[count]);
	return (count);
}

int	get_format(char c, va_list args)
{
	int		count;

	count = 0;
	if (c == 'c')
		count += print_char(va_arg(args, int));
	else if (c == 's')
		count += print_string(va_arg(args, char *));
	else if (c == 'p')
		count += print_pointer(va_arg(args, void *));
	else if (c == 'd' || c == 'i')
		count += print_dec_signed(va_arg(args, int));
	else if (c == 'u')
		count += print_dec_unsigned(va_arg(args, unsigned int));
	else if (c == 'x')
		count += print_hex_lower(va_arg(args, unsigned int));
	else if (c == 'X')
		count += print_hex_upper(va_arg(args, unsigned int));
	else if (c == '%')
		count += print_char('%');
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;
	int		i;

	count = 0;
	i = 0;
	if (str == NULL)
		return (-1);
	va_start(args, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			count += get_format(str[i], args);
		}
		else
			count += print_char(str[i]);
		i++;
	}
	va_end(args);
	return (count);
}
