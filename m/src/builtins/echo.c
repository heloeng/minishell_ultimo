
#include "minishell.h"

void ft_echo(t_data_val *data, char **parser_i)
{
	int i;
	int new_line;

	i = 1;
	new_line = 1;
	while (parser_i[i] && ft_strncmp(parser_i[i], "-n", 3) == 0)
	{
		new_line = 0;
		i++;
	}
	while (data->token[i])
	{
        if (parser_i[i][0] == '\'' && parser_i[i][ft_strlen(parser_i[i]) - 1] == '\'' && ft_strlen(parser_i[i]) >= 2)
            print_single_quoted(parser_i[i]);
        else if (parser_i[i][0] == '"' && parser_i[i][ft_strlen(parser_i[i]) - 1] == '"' && ft_strlen(parser_i[i]) >= 2)
            print_double_quoted(data->token[i], data);
        else if (ft_strchr(parser_i[i], '$') && !was_single_quoted(data->text, parser_i[i]))
            print_with_expansion(parser_i[i], data);
        else
            ft_printf("%s", parser_i[i]);
		if (parser_i[i + 1]) ft_printf(" ");
		i++;
	}
	if (new_line)
		ft_printf("\n");
}