# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: helde-so <helde-so@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/18 13:47:39 by helde-so          #+#    #+#              #
#    Updated: 2024/12/02 13:08:55 by helde-so         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = cc                 
CFLAGS = -Wall -Wextra -Werror -I .
SRC = ft_printf.c ft_printchar.c ft_print_string.c ft_print_pointer.c ft_print_hexa_upper.c ft_print_hexa_lower.c ft_print_dec_unsigned.c ft_print_dec_int.c  


OBJ = $(SRC:.c=.o)       

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re