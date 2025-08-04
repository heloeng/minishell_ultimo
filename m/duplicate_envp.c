#include "minishell.h"

/*
Cria uma cópia independente do array envp (passadas no main()), 
para que o (minishell) modifique com segurança.
O envp original recebido no main() foi criado pelo sistema operacional, 
e não pode fazer free(), realloc() ou strdup() , pois da erros como:
invalid pointer, munmap_chunk() , core dumped
*/
char **duplicate_envp(char **envp)
{
	int count = 0;
	int i = 0;
	char **new_env;

	while (envp[count])
		count++;

	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return NULL;

	while (i < count)
	{
		new_env[i] = ft_strdup(envp[i]);
		i++;
	}
	new_env[i] = NULL;
	return new_env;
}
