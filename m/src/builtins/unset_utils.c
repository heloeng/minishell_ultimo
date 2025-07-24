
#include "minishell.h"

/*
args	char **	O vetor de argumentos do usuário (ex: unset VAR1 VAR2)
data	t_data_val *	Sua struct principal, que contém o envp atual
unset HELLO HOME PATH
args[0] = "unset"
args[1] = "HELLO"
args[2] = "HOME"
args[3] = "PATH"
args[4] = NULL

A função ft_unset_args vai percorrer de i = 1 em diante, chamando:
ft_unset(&data->envp, "VAR1");
ft_unset(&data->envp, "VAR2");
ft_unset(&data->envp, "VAR3");
Ela ignora o args[0] ("unset") e começa do índice 1, 
removendo cada nome do ambiente.
*/
int ft_unset_args(char **args, t_data_val *data)
{
	int i = 1;

	while (args[i]) // enquanto tiver variáveis após "unset"
	{
		ft_unset(&data->envp, args[i]); // remove cada uma
		i++;
	}
	return (0); // sucesso (exit code 0)
}


// cria um novo envp sem a variável name.
char **build_new_env(char **old, const char *name)
{
	char **new;
	int i;
	int j;
	int len;

	i = 0;
	j = 0;
	len = ft_strlen(name);
	while (old[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1)); // +1 pro NULL final
	if (!new)
		return NULL;
	i = 0;
	while(old[i])
	{
		if(!(ft_strncmp(old[i], name, len) == 0 && old[i][len] == '='))
			new[j++] = ft_strdup(old[i]);
		i++;
	}
	new[j] = NULL;
	return new;
}
