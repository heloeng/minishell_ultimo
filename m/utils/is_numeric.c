
#include "minishell.h"

/*Retorna 1 se a string for só composta por dígitos ("42", "0", "123456")
Retorna 0 se tiver qualquer caractere não numérico ("abc", "42a", "")
*/

int	ft_isnumeric(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')  
		i++;
	if (!ft_isdigit(str[i]))             
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
