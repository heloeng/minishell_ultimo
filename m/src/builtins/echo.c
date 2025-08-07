
#include "minishell.h"
void ft_echo(t_data_val *data)
{
	int i;
	int new_line;

	i = 1;
	new_line = 1;
	while (data->token[i] && ft_strncmp(data->token[i], "-n", 3) == 0)
	{
		new_line = 0;
		i++;
	}
	while (data->token[i])
	{
        if (data->token[i][0] == '\'' && data->token[i][ft_strlen(data->token[i]) - 1] == '\'' && ft_strlen(data->token[i]) >= 2)
            print_single_quoted(data->token[i]);
        else if (data->token[i][0] == '"' && data->token[i][ft_strlen(data->token[i]) - 1] == '"' && ft_strlen(data->token[i]) >= 2)
            print_double_quoted(data->token[i], data);
        else if (ft_strchr(data->token[i], '$') && !was_single_quoted(data->text, data->token[i]))
            print_with_expansion(data->token[i], data);
        else
            ft_printf("%s", data->token[i]);
		if (data->token[i + 1]) ft_printf(" ");
		i++;
	}
	if (new_line)
		ft_printf("\n");
}
