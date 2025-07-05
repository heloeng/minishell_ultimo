
#include "minishell.h"

/*Retorna 1 se a string for só composta por dígitos ("42", "0", "123456")
Retorna 0 se tiver qualquer caractere não numérico ("abc", "42a", "")
*/

int ft_isnumeric(const char *str)
{
    int i;

    if(str[0] == '\0')
    {
        return (0);
    }

    i = 0;
    while(str[i])
    {
         if(!ft_isdigit((unsigned char)str[i]))
            return (0);
         i++;
    }
    return (1);
    
}