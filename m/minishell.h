/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:20:08 by dydaniel          #+#    #+#             */
/*   Updated: 2025/08/13 22:40:31 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "ft_printf/ft_printf.h"
# include <signal.h>
# include <unistd.h>     
# include <sys/types.h> 
# include <sys/wait.h>  
# include <limits.h>
# include <fcntl.h> 


typedef struct s_data_val
{
	int		argc;
	char	**envp;
	int		**fd;
	char	*text;
	char	**token;
	char	***parser;
	char	*path;
	char	*envp_path;
	char	**cmd_path;
	int		num_pipes;
	pid_t	*child_pid;
	int		last_exit;
}	t_data_val;

typedef enum e_redir_heredoc
{
	NO_RD_HD,
	RD_IN,
	RD_OUT,
	APPEND,
	HEREDOC
}	t_redir_heredoc;

typedef enum e_builtin_flag
{
	NO_BUILTIN,
	CD,
	ECHO,
	EXPORT,
	PWD,
	ENV,
	UNSET,
	EXIT
}	t_builtin_flag;

extern int	g_exit_status;

char	**duplicate_envp(char **envp);
//quote handling
char	*complete_unclosed_quote(char *text);
int		has_unclosed_quote(char *str);
int		char_inside_quotes(const char *str, int index);

//PREPROCESSORS
char	*get_env_value(char *name, char **envp);
void	change_signal_exec(t_data_val *data, int *status);
void	configure_signal(void);
void	configure_signal_childs(void);

//validate pipe
int		validate_pipe_syntax(const char *input);
int		starts_with_pipe(const char *input);
int		contains_double_pipe(const char *input);
int		contains_pipe_space_pipe(const char *input);
int		ends_with_pipe(const char *input);

//BUILTINS
int		check_builtin(char *cmd);
int		execute_builtin(t_data_val *data, char **token);

//echo
void	ft_echo(t_data_val *data, char **parser_i);

//echo utils
void	print_with_expansion(char *str, t_data_val *data);
int		handle_dollar_expansion(char *str, t_data_val *data);
void	print_expanded_var(char *var_name, char **envp);
int 	token_was_single_quoted_advance(const char **cursor, const char *token);
void 	expand_loop(char *str, t_data_val *data);


//unset
void	ft_unset(char ***envp, char *name);
int		ft_unset_args(char **args, t_data_val *data);
char	**build_new_env(char **old, const char *name);

//cd
int		run_cd(char *path);
int		analize_cd_arguments(t_data_val *data, char **token);

//exit
int		ft_exit(char **parser_i);

//pwd
void	ft_pwd(void);

//env
void	ft_env(t_data_val *data, char **parser_i);
void	update_env(char ***envp, char *arg);

//export
int		ft_export(char **args, t_data_val *data);

void	add_new_var(char ***envp, char *arg);
int		replace_existing_var(char **envp, char *name, char *arg);
int		is_valid_identifier(char *arg);
int		ft_export(char **args, t_data_val *data);

//general auxiliars fuctions
int		ft_isnumeric(const char *str);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
void	ft_putstr_fd(const char *s, int fd);
int		ft_isalpha(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_isnumeric_with_sign(const char *s);
void	ft_putchar_fd(char c, int fd);
long	ft_atoi_base(const char *nptr, int base);
char	*ft_itoa(int n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strcpy_quote(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s);
int		ft_isspace(char c);

//TOKEN
void	divide_arguments(char ***token, char *text);
void	populate_token(char **token, char *text, int n_token);
int		num_tokens(char *text);

//TOKEN_AUX
int		is_operator(char *text);
int		size_of_string(char *text);
int		size_of_quote(char *text);
char	*check_path(t_data_val *data, char *cmd);
void	get_full_path(t_data_val **data);
void	change_dolar_sign(char ***token);

//PARSER
void	parse_token(t_data_val **data);
void	change_fd(t_data_val *data, int redir_heredoc, int i, int j);

//EXECUTION
void	exc_command(t_data_val *data);
void	exec_child_process(t_data_val *data, int i);
void	exec_one_command(t_data_val *data, int *status);
int		solo_command_redir_heredoc(char **token, int i);
void	close_unused_fd(t_data_val *data, int i);
void	first_pipe(t_data_val *data, int flag, int i);
void	middles_pipe(t_data_val *data, int flag, int i);
void	last_pipe(t_data_val *data, int flag, int i);
char	**clear_parser(char **parser);

//REDIR_HEREDOC
int		check_redir_herdoc(t_data_val *data, int i);
void	pipe_heredoc(t_data_val *data, char **parser, int j, int i);
void	solo_heredoc_fd(char **token, int i, int *fd);

void	handle_command(t_data_val *data);
void	handle_ctrlc(int sig);
void	free_after_command(t_data_val *data);

//FREE ALL
void	free_data(t_data_val *data);
void	free_fd(int ***fd);
void	free_tokens(char ***token);
void	free_parser(t_data_val *data);

//remove
void	print_tokens(char **token);
void	parse_token(t_data_val **data);
#endif
