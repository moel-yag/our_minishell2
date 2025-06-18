# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline -Llibft -lft #-fsanitize=address

# Directories
LIBFT_DIR = libft
INCLUDES = -Iincludes -I$(LIBFT_DIR)/includes

# Source files (removed libft functions)
SRC = parsing/test_parsing.c\
	  parsing/parsing.c\
	  tokens/tokenizer.c\
	  tokens/test_tokenizer.c\
	  expansion/expansion.c\
	  expansion/test_expansion.c\

# Object files
OBJ = $(SRC:.c=.o)

# Output binary name
NAME = minishell

# Default target
all: libft $(NAME)

# Build libft first
libft:
	@$(MAKE) -C $(LIBFT_DIR) bonus

# Linking the binary
$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

# Compiling object files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Cleaning object files
clean:
	rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean

# Cleaning everything
fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re libft