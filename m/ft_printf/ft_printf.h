/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:46:54 by helde-so          #+#    #+#             */
/*   Updated: 2024/11/26 18:31:30 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stddef.h>

unsigned long	ft_print_pointer(void *p);
int				ft_printf(const char *str, ...);
int				ft_formats(char c, va_list args);
int				ft_printchar(char c);
int				ft_print_dec_int(int n);
int				ft_print_dec_unsigned(unsigned int n);
int				ft_print_hexa_lower(unsigned long n);
int				ft_print_hexa_upper(unsigned long n);
int				ft_print_string(char *str);
int				ft_printchar(char c);

#endif