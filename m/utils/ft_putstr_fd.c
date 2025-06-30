/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:28:36 by helde-so          #+#    #+#             */
/*   Updated: 2025/06/30 15:48:06 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_fd(const char *s, int fd)
{
	const char *ptr = s;

	ptr = s;
	while (*ptr != '\0')
	{
		write(fd, ptr, 1);
		ptr++;
	}
}
