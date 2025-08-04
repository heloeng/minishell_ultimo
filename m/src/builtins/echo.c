
#include "minishell.h"
//!DIMINUIR FUNCAO
void ft_echo(t_data_val *data)
{
	int i;
	int new_line;
    char *clean;

	i = 1;
	new_line = 1;
	while (data->token[i] && ft_strncmp(data->token[i], "-n", 3) == 0)
	{
		new_line = 0;
		i++;
	}
	while (data->token[i])
	{
        if (data->token[i][0] == '\'' && data->token[i][ft_strlen(data->token[i]) - 1] == '\'')
			print_single_quoted(data->token[i]);//trata tokens entre aspas simples (')
		else if (data->token[i][0] == '"' && data->token[i][ft_strlen(data->token[i]) - 1] == '"')
            print_double_quoted(data->token[i], data->envp);//trata tokens entre aspas duplas (")
		else if (ft_strchr(data->token[i], '$'))// Caso: variável fora de aspas
			print_with_expansion(data->token[i], data->envp);
		else
        {
            clean = remove_all_quotes(data->token[i]);
			// ft_printf("%s", data->token[i]); // Caso: texto simples, sem aspas ou $
			ft_printf("%s", clean); // Caso: texto simples, sem aspas ou $
            free(clean);
        }
		if (data->token[i + 1]) ft_printf(" ");
		i++;
	}
	if (new_line)
		ft_printf("\n");
}
