/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:20:08 by dydaniel          #+#    #+#             */
/*   Updated: 2025/07/05 18:38:22 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <readline/readline.h>
#include <readline/history.h>
# include "ft_printf/ft_printf.h"
#include <signal.h>
#include <unistd.h>     
#include <sys/types.h> 
#include <sys/wait.h>  
#include <limits.h>

/* Estrutura para armazenar dados
fd[2] -> usado no pipe. Necessário para exercutar comando de |
text -> input do terminal
token -> tokenização do texto
path -> caminho absoluto do comando, quando existir
child_pid -> pid do processo filho

*/
typedef struct s_data_val
{
    int argc;
    char **envp;
    int **fd;
    char *text;
    char **token;
    char ***parser;
    char *path;
    char *envp_path;
    int num_pipes;
    pid_t *child_pid;
}   t_data_val;


char *get_env_value(char *name, char **envp);
void ft_unset(char ***envp, char *name);
void    ft_putstr_fd(const char *s, int fd);
int     ft_isalpha(int c);
char   *ft_strchr(const char *s, int c);
char   *ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
int execute_builtin(t_data_val *data);
void	add_new_var(char ***envp, char *arg);
int	replace_existing_var(char **envp, char *name, char *arg);
void	update_env(char ***envp, char *arg);
int is_valid_identifier(char *arg);
int	ft_export(char **args, t_data_val *data);
int analize_cd_arguments(t_data_val *data);
int run_cd(char *path);
void ft_echo(t_data_val *data);
int is_n_flag(const char *str);
void ft_env(t_data_val *data);
void ft_pwd(t_data_val *data);
int ft_exit(t_data_val *data);
int ft_isnumeric(const char *str);
int	ft_isdigit(int c);
int ft_isalnum(int c);

long	ft_atoi_base(const char *nptr, int base);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t ft_strcpy_quote(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
int ft_isspace(char c);
void    configure_signal();
void handle_command(t_data_val *data);
void    handle_ctrlc(int sig);
void divide_arguments(char ***token, char *text);
int num_tokens(char *text);
void free_tokens(char ***token);
void populate_token(char **token, char *text);
int size_of_str(char *text);
int a_comma(char *c, char c_text);
char *check_path(char **token, char **envp);
void exc_command(t_data_val *data);
void free_parser(t_data_val *data);
//remove
void print_tokens(char **token);
void parse_token(t_data_val **data);
#endif
