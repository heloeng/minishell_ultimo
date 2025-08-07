
#include "minishell.h"

void ft_pwd(t_data_val *data)
{
    char cwd[1024];
    (void)data;
    if(getcwd(cwd, sizeof(cwd)) == NULL)
    {
        ft_printf("pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
        return;
    }
    ft_putstr_fd(cwd, 1);
    ft_putstr_fd("\n", 1);
}