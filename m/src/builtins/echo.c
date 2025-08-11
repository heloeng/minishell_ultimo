
#include "minishell.h"


//entre ' ' , " " ou sem aspas
static t_qtype	q_at(const char *cmd, const char *p, size_t len)
{
	int		has_before;
	char	before;
	char	after;

	has_before = (p != cmd);
	if (has_before)
		before = *(p - 1);
	else
		before = '\0';
	after = *(p + len);
	if (before == '\'' && after == '\'')
		return (Q_SINGLE);
	if (before == '"' && after == '"')
		return (Q_DOUBLE);
	return (Q_NONE);
}

//próxima ocorrência do token
static t_qtype	q_next(const char *cmd, const char *tok, size_t *from)
{
	size_t		len;
	const char	*p;
	t_qtype		qt;

	len = ft_strlen(tok);
	p = cmd + *from;
	while ((p = ft_strnstr(p, tok, ft_strlen(p))))
	{
		qt = q_at(cmd, p, len);
		if (qt != Q_NONE)
		{
			*from = (size_t)(p - cmd) + len;
			return (qt);
		}
		p += 1;
	}
	return (Q_NONE);
}

static void	echo_print_token(t_data_val *data, char *tok, size_t *from)
{
	t_qtype	q;

	q = q_next(data->text, tok, from);
	if (q == Q_SINGLE)
		ft_printf("%s", tok);
	else if (q == Q_DOUBLE || ft_strchr(tok, '$'))
		print_with_expansion(tok, data);
	else
		ft_printf("%s", tok);
}

void	ft_echo(t_data_val *data)
{
	int		i;
	int		new_line;
	size_t	from;

	i = 1;
	new_line = 1;
	from = 0;
	while (data->token[i] && ft_strncmp(data->token[i], "-n", 3) == 0)
	{
		new_line = 0;
		i++;
	}
	while (data->token[i])
	{
		echo_print_token(data, data->token[i], &from);
		if (data->token[i + 1])
			ft_printf(" ");
		i++;
	}
	if (new_line)
		ft_printf("\n");
}


