NAME = minishell
CC = cc
DIR_PRINT = ft_printf
LDFLAGS = -lreadline
DIR_UTILS = utils
SRC_DIR := src
BUILDINS_DIR := $(SRC_DIR)/builtins
FLAGS = -Wall -Werror -Wextra -I. -I${DIR_PRINT}
SOURCES = \
	  $(DIR_PRINT)/ft_print_dec_int.c \
	  $(DIR_PRINT)/ft_print_dec_unsigned.c \
	  $(DIR_PRINT)/ft_print_hexa_lower.c \
	  $(DIR_PRINT)/ft_print_hexa_upper.c \
	  $(DIR_PRINT)/ft_print_pointer.c \
	  $(DIR_PRINT)/ft_print_string.c \
	  $(DIR_PRINT)/ft_printchar.c \
	  $(DIR_PRINT)/ft_printf.c \
	  $(DIR_UTILS)/ft_atoi_base.c \
	  $(DIR_UTILS)/ft_strlcpy.c \
	  $(DIR_UTILS)/ft_toupper.c \
	  $(DIR_UTILS)/ft_split.c \
	  $(DIR_UTILS)/ft_strtrim.c \
	  $(DIR_UTILS)/ft_strlen.c \
	  $(DIR_UTILS)/ft_strjoin.c \
	  $(DIR_UTILS)/ft_strlcat.c \
	  $(DIR_UTILS)/ft_isspace.c \
	  $(DIR_UTILS)/ft_strdup.c \
	  $(DIR_UTILS)/ft_strncmp.c \
	  $(DIR_UTILS)/ft_isdigit.c\
	  $(DIR_UTILS)/is_numeric.c\
	  $(DIR_UTILS)/ft_isalpha.c\
	  $(DIR_UTILS)/ft_strchr.c\
	  $(DIR_UTILS)/ft_putstr_fd.c\
	  $(DIR_UTILS)/ft_substr.c\
	  $(DIR_UTILS)/ft_isalnum.c\
	  $(DIR_UTILS)/ft_putchar_fd.c\
	  $(DIR_UTILS)/quote_utils.c\
	  $(DIR_UTILS)/ft_itoa.c\
	  $(DIR_UTILS)/ft_calloc.c\
	  $(DIR_UTILS)/ft_bzero.c\
	  $(DIR_UTILS)/ft_memset.c\
	  $(DIR_UTILS)/ft_strnstr.c\
	  $(BUILDINS_DIR)/echo.c \
	  $(BUILDINS_DIR)/echo_utils.c \
	  $(BUILDINS_DIR)/unset.c \
	  $(BUILDINS_DIR)/export.c \
	  $(BUILDINS_DIR)/export_utils.c \
	  $(BUILDINS_DIR)/cd.c \
	  $(BUILDINS_DIR)/env.c \
	  $(BUILDINS_DIR)/cd_utils.c \
	  $(BUILDINS_DIR)/exit.c \
	  $(BUILDINS_DIR)/pwd.c \
	  minishell.c token_working.c token_aux.c handle_command.c redir_heredoc.c\
	  configure_signals.c pipes_parser.c get_path.c exec_childs.c\
	  exec_pipes.c solo_redir_heredoc.c\
	  execute_builtin.c parser_clear.c heredoc.c\
	  validate_inputs.c\
	  duplicate_envp.c free_data.c


OBJECTS = $(SOURCES:.c=.o)

all: ${NAME}

${NAME}: ${OBJECTS}
	@${CC} ${FLAGS} ${OBJECTS} $(LDFLAGS) -o ${NAME}

%.o: %.c
	@${CC} ${FLAGS} -c $< -o $@

clean:
	@rm -f ${OBJECTS}

fclean: clean
	@rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
