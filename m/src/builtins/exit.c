
#include "minishell.h"

int ft_exit(t_data_val *data)
{
	long long	exit_code;

	if (data->token[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		data->last_exit = 1;      
		return (1);            
	}
	if (data->token[1])
	{
		if (!ft_isnumeric_with_sign(data->token[1]))
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(data->token[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(2);      
		}
		exit_code = ft_atoi_base(data->token[1], 10);
		exit((unsigned char)exit_code);  
	}
	exit(0);
	return (0);   
}