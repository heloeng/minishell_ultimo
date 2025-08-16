/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:20:08 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/15 21:47:47 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <ctype.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <errno.h>

extern int	g_in_prompt;

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC
}	t_token_type;

// Represents a lexical token in the shell input
// (e.g., command, operator, word)
typedef struct s_token
{
	char			*value;
	t_token_type	type;
	char			quote_type;
	struct s_token	*next;
}	t_token;

// Represents a redirection
// (e.g., > file, < input.txt)
typedef struct s_redirect
{
	t_token_type		type;
	char				*file;
	struct s_redirect	*next;
}	t_redirect;

// Represents a parsed shell command with arguments and redirections
typedef struct s_command
{
	char				**argv;
	t_redirect			*redirects;
	struct s_command	*next;
}	t_command;

// Represents a single environment variable
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

// Holds execution-related data used during command execution
typedef struct s_exec_data
{
	int		prev_fd;
	pid_t	last_pid;
	int		pipefd[2];
}	t_exec_data;

// Context used during variable expansion
// (e.g., replacing $VAR or $? in input)
typedef struct s_expander_context
{
	const char	*input;
	int			*i;
	char		**res;
	t_env		*env;
	int			last_exit_status;
}	t_expander_context;

// Represents the global shell state
typedef struct s_shell
{
	int		last_exit_status;
	t_env	*env;
	int		should_exit;
	int		exit_code;
}	t_shell;

// signals
void		handle_signals(void);

// loop
void		minishell_loop(t_shell *shell);
int			is_command_valid(t_command *cmd, t_env *env);
int			process_invalid_cmd(t_shell *shell, t_command *cmd);

// readline
char		*read_input(void);

// lexer
t_token		*lexer(char *input);
void		append_token_to_list(t_token **list, t_token *new);
t_token		*new_token(char *value, t_token_type type,
				char quote_type);

// parser
int			check_syntax_errors(t_token *tokens);
int			is_builtin(char *cmd);
t_command	*parser(t_token *tokens);
t_command	*init_command(t_command **cmd_head);
void		add_token_to_cmd(t_token **token, t_command **current_cmd,
				t_command **cmd_head);

// expander
void		expand_all(t_command *cmd_head, t_env *env,
				int last_exit_status);
void		handle_expansion(t_expander_context *ctx);
char		*extract_var_name(const char *input, int *i);
void		append_str(char **dst, const char *src);
int			count_args(char **argv);

// executor
void		executor(t_command *cmd_head, t_shell *shell);
pid_t		setup_pipe_and_fork(t_command *current_cmd, int *pipefd);
void		execute_single_command(t_command *current_cmd, char **envp,
				t_shell *shell, t_exec_data *data);
void		handle_parent_process(t_command *current_cmd, pid_t pid,
				t_exec_data *data);
void		dup_and_close(int oldfd, int newfd);
void		handle_redirections(t_redirect *redir);
char		*search_in_path(char *cmd, t_env *env);
void		handle_execve(char *cmd_path, char **argv,
				char **envp, struct stat *st);

// builtin
void		exec_builtin(t_command *current_cmd, t_shell *shell);
int			builtin_export(char **argv, t_env **env,
				t_shell *shell);
int			builtin_unset(char **argv, t_env **env);
int			builtin_exit(char **argv, t_shell *shell);
int			builtin_cd(char **argv, t_shell *shell);

// env
t_env		*new_env_node(char *key, char *value);
void		add_env_back(t_env **env_list, t_env *new_node);
t_env		*create_env_list(char **envp);
int			count_env(t_env *env, int with_value_only);
char		**env_list_to_array(t_env *env);
void		print_env(t_env *env);
int			update_or_add_env(t_env **env, char *key,
				char *value, int has_value);			
char		*get_env_var(t_env *env, const char *key);

// free
void		free_env_array(char **env_array);
void		free_env_list(t_env *env);
void		free_env_node(t_env *env);
void		free_cmds(t_command *cmd_head);
void		free_token_list(t_token *tokens);
void		free_redirects(t_redirect *redir);

#endif