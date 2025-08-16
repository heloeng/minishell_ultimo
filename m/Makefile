# Program Name
NAME = minishell

# Compiler
CC = cc

# Compiler Flags
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -I/opt/homebrew/opt/readline/include

# Required Libraries
LIBS = -lreadline -lncurses -L/opt/homebrew/opt/readline/lib
LIBFT = libft/libft.a

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# Source Files
SRCS = $(SRC_DIR)/01-main.c \
		$(SRC_DIR)/02-signals.c \
		$(SRC_DIR)/03.1-loop.c \
		$(SRC_DIR)/03.2-loop_utils.c \
		$(SRC_DIR)/04-readline.c \
		$(SRC_DIR)/05.1-lexer.c \
		$(SRC_DIR)/05.2-lexer_utils.c \
		$(SRC_DIR)/06.1-parser.c \
		$(SRC_DIR)/06.2-parser.c \
		$(SRC_DIR)/06.3-parser.c \
		$(SRC_DIR)/07.1-expander.c \
		$(SRC_DIR)/07.2-expander.c \
		$(SRC_DIR)/07.3-expander.c \
		$(SRC_DIR)/08.1-executor.c \
		$(SRC_DIR)/08.2-executor.c \
		$(SRC_DIR)/08.3-executor.c \
		$(SRC_DIR)/08.4-executor.c \
		$(SRC_DIR)/09.1-builtin.c \
		$(SRC_DIR)/09.2-builtin.c \
		$(SRC_DIR)/09.3-builtin.c \
		$(SRC_DIR)/09.4-builtin.c \
		$(SRC_DIR)/10.1-env.c \
		$(SRC_DIR)/10.2-env.c \
		$(SRC_DIR)/10.3-env.c \
		$(SRC_DIR)/10.4-env.c \
		$(SRC_DIR)/10.5-env.c \

# Generated Objects
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Rule to Compile Program
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS) $(LIBFT)
	
$(LIBFT):
	make -C libft

# Rule to Compile .c to .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Create obj directory, if not exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean .o
clean:
	rm -rf $(OBJ_DIR)
	make -C libft clean

# Clean all
fclean: clean
	rm -f $(NAME)
	make -C libft fclean

# Recompile
re: fclean all

.PHONY: all clean fclean re