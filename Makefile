C = gcc
AR = ar
LIBFT_DIR = libft
LIBFT_NAME = libft.a
MAKE = make
NAME = minishell
flags = -Wall -Wextra -Werror
SRCS = srcs/minishell.c srcs/get_next_line.c
BSRCS = 
all : $(NAME)
$(NAME):
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $(flags) $(SRCS) $(LIBFT_DIR)/$(LIBFT_NAME) -o $(NAME)

bonus:
	@$(CC) $(flags) $(BSRCS) $(LIBFT_DIR)/$(LIBFT_NAME) -o $(NAME)

clean: 
	@rm -rf $(LIBFT_DIR)/*.o

fclean: clean
	@rm -rf $(NAME) $(LIBFT_DIR)/$(LIBFT_NAME)

re: fclean all
	@echo "Rebuilding Library."