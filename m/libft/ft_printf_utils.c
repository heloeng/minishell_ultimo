/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:48:45 by helde-so          #+#    #+#             */
/*   Updated: 2025/08/15 21:43:27 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_dec_signed(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		print_string("-2147483648");
		return (11);
	}
	else if (n < 0)
	{
		print_char('-');
		n = -n;
		count++;
	}
	if (n >= 10)
		count += print_dec_signed(n / 10);
	print_char("0123456789"[n % 10]);
	return (count + 1);
}

int	print_dec_unsigned(unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 10)
		count += print_dec_unsigned(n / 10);
	print_char("0123456789"[n % 10]);
	return (count + 1);
}

int	print_hex_upper(unsigned long n)
{
	int	count;

	count = 0;
	if (n >= 16)
		count += print_hex_upper(n / 16);
	print_char("0123456789ABCDEF"[n % 16]);
	return (count + 1);
}

int	print_hex_lower(unsigned long n)
{
	int	count;

	count = 0;
	if (n >= 16)
		count += print_hex_lower(n / 16);
	print_char("0123456789abcdef"[n % 16]);
	return (count + 1);
}

unsigned long	print_pointer(void *p)
{
	unsigned long	len;
	unsigned long	pnt;

	if (p == NULL)
	{
		print_string("(nil)");
		return (5);
	}
	pnt = (unsigned long)p;
	print_string("0x");
	len = print_hex_lower(pnt);
	return (len + 2);
}
