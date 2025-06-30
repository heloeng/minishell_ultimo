/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_export.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:34:55 by helde-so          #+#    #+#             */
/*   Updated: 2025/06/30 19:34:56 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

//!verificar se há necessidade de fazer export VAR E export sem argumento

int	ft_export(char **args, t_data_val *data)
{
    int i;
	int status;

	status = 0;
    i = 1;
    while(args[i])
    {
        if(!is_valid_identifier(args[i]))
		{
            ft_printf("export: %s: not a valid identifier\n", args[i]);
            status = 1; 
		} 
        else
            update_env(&data->envp, args[i]);
        i++;
    }
    return (status);
}

int is_valid_identifier(char *arg)//função garante que o nome da variável siga o padrão do bash:
{
    int i;

    i = 0;
    if(!ft_isalpha(arg[0]) && arg[0] != '_')
    {
        return (0);// inválido se começar com número ou símbolo
    }
    while(arg[i] && arg[i] != '=')
    {
        if(!ft_isalnum(arg[i]) && arg[i] != '_')
            return (0);// se tiver caractere inválido (ex: !, -, %, etc), retorna falso
        i++;
    }
    return (1);
}

void	update_env(char ***envp, char *arg)
{
	char	*name;
	char	*equal;

	equal = ft_strchr(arg, '=');
	if (!equal)
		return; // Se não tiver '=', não faz nada

	name = ft_substr(arg, 0, equal - arg);

	if (replace_existing_var(*envp, name, arg))
	{
		free(name); // libera memória do nome
		return;     // se substituiu, sai
	}

	add_new_var(envp, arg);	// Se não substituiu, adiciona uma nova variável
	free(name); 
}

int	replace_existing_var(char **envp, char *name, char *arg)//Verifica se já existe e substitui
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(name);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, len) && envp[i][len] == '=')
		{
			free(envp[i]);// Se encontrou, libera a antiga e coloca a nova
			envp[i] = ft_strdup(arg);
			return (1); // substituição feita
		}
		i++;
	}
	return (0); // não encontrou para substituir
}

void	add_new_var(char ***envp, char *arg)
{
	int		count;
	int		i;
	char	**new_env;

	count = 0;
	while ((*envp)[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return;
	i = 0;
	while (i < count)
	{
		new_env[i] = (*envp)[i];
		i++;
	}
	new_env[count] = ft_strdup(arg);
	new_env[count + 1] = NULL;

	free(*envp);
	*envp = new_env;
}


