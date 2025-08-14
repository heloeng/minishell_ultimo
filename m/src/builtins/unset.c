/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:35:06 by helde-so          #+#    #+#             */
/*   Updated: 2025/08/13 22:33:57 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char ***envp, char *name)
{
	char	**old;
	char	**new;

	if (!envp || !*envp || !name)
		return;
	old = *envp;
	new = build_new_env(old, name);
	if (!new)
		return;
	free(old);
	*envp = new;
}


