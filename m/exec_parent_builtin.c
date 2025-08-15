#include "minishell.h"

int	is_parent_builtin(int flag)
{
	return (flag == CD || flag == EXPORT || flag == UNSET || flag == EXIT);
}
//salva stdin/stdout
void	save_stdio(int *save_in, int *save_out)
{
	*save_in = dup(STDIN_FILENO);
	*save_out = dup(STDOUT_FILENO);
}
//restaura stdin/stdout
void	restore_stdio(int save_in, int save_out)
{
	if (save_in >= 0)
	{
		dup2(save_in, STDIN_FILENO);
		close(save_in);
	}
	if (save_out >= 0)
	{
		dup2(save_out, STDOUT_FILENO);
		close(save_out);
	}
}
//redireçiona e limpa tokens
int	parent_builtin_apply_redirs(t_data_val *data)
{
	int	redir_flag;

	redir_flag = solo_command_redir_heredoc(data->token, 0);
	if (redir_flag != NO_RD_HD)
		data->token = clear_parser(data->token);
	return (redir_flag);
}

/* executa builtin de PAI (cd/export/unset/exit) com redireção aplicada
   retorna 1 se tratou aqui; 0 se não era builtin de pai */
int	run_parent_builtin_single(t_data_val *data, int *status)
{
	int	flag;
	int	save_in;
	int	save_out;

	if (!data->token || !data->token[0])
		return (0);
	flag = check_builtin(data->token[0]);
	if (flag == NO_BUILTIN || !is_parent_builtin(flag))
		return (0);
	save_stdio(&save_in, &save_out);
	parent_builtin_apply_redirs(data);
	execute_builtin(data, data->token);
	data->last_exit = g_exit_status;
	if (status)
		*status = (g_exit_status & 0xFF);
	restore_stdio(save_in, save_out);
	return (1);
}
