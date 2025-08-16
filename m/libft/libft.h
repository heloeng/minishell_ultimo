/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:28:44 by helde-so          #+#    #+#             */
/*   Updated: 2025/08/15 21:47:05 by helde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// Function declarations
int				ft_atoi(const char *nptr);
long			ft_atol(const char *nptr);
void			ft_bzero(void *s, size_t len);
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
char			*ft_itoa(int n);

void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
t_list			*ft_lstnew(void *content);
int				ft_lstsize(t_list *lst);

void			*ft_memchr(const void *str, int c, size_t len);
int				ft_memcmp(const void *str1, const void *str2, size_t len);
void			*ft_memcpy(void *dest, const void *src, size_t len);
void			*ft_memmove(void *dest, const void *src, size_t len);
void			*ft_memset(void *s, int c, size_t len);

// ft_printf
int				print_dec_signed(int n);
int				print_dec_unsigned(unsigned int n);
int				print_hex_upper(unsigned long n);
int				print_hex_lower(unsigned long n);
unsigned long	print_pointer(void *p);
int				print_char(char c);
int				print_string(char *str);
int				get_format(char c, va_list args);
int				ft_printf(const char *str, ...);

void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *str, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *str, int fd);
char			**ft_split(char const *str, char c);
char			*ft_strcat(char *dest, const char *src);
char			*ft_strchr(const char *str, int nb);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strcpy(char *dest, char *src);
char			*ft_strdup(const char *src);
void			ft_striteri(char *str, void (*f)(unsigned int, char*));
char			*ft_strjoin(char const *str1, char const *str2);
size_t			ft_strlcat(char *dest, const char *src, size_t len);
size_t			ft_strlcpy(char *dest, const char *src, size_t len);
size_t			ft_strlen(const char *str);
int				ft_strncmp(const char *str1, const char *str2, size_t len);
char			*ft_strncpy(char *dest, char *src, unsigned int n);
char			*ft_strndup(const char *s, size_t n);
char			*ft_strmapi(char const *str, char (*f)(unsigned int, char));
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_strrchr(const char *str, int nb);
char			*ft_strtrim(char const *str1, char const *set);
char			*ft_substr(char const *str, unsigned int start, size_t len);
int				ft_tolower(int c);
int				ft_toupper(int c);

char			*get_next_line(int fd);

#endif
