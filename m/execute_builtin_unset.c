
#include "minishell.h"
void ft_unset(char ***envp, char *name)
{
	char **old;
	char **new;
	int i;
	int j;
	int len;
	
	old = *envp;
	i = 0;
	j = 0;
	len = ft_strlen(name);
	while (old[i])
	{
		i++;
	}
	if(!(new = malloc(sizeof(char *) * (i + 1))))
		return;
	i = 0;
	while(old[i])
	{
		if(!(ft_strncmp(old[i], name, len) == 0 && old[i][len] == '='))
		{
			new[j++] = old[i];
		}
		else
		{
			free(old[i]);
		}
		i++;
	}
	new[j] = NULL;
	free(old);
	*envp= new;
}