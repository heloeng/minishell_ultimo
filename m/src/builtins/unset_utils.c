
#include "minishell.h"

int	ft_unset_args(char **args, t_data_val *data)
{
	int	i;

	i = 1;
	while (args[i])
	{
		ft_unset(&data->envp, args[i]);
		i++;
	}
	return (0);
}

char	**build_new_env(char **old, const char *name)
{
	char	**new;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = ft_strlen(name);
	while (old[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (old[i])
	{
		if (!(ft_strncmp(old[i], name, len) == 0 && old[i][len] == '='))
			new[j++] = ft_strdup(old[i]);
		i++;
	}
	new[j] = NULL;
	return (new);
}
