C = gcc
AR = ar
LIBFT_DIR = libft
LIBFT_NAME = libft.a
MAKE = make
NAME = minishell
flags = -Wall -Wextra -Werror
SRCS = srcs/minishell.c srcs/get_next_line.c srcs/get_next_line_utils.c srcs/wsh_exec.c srcs/wsh_garbageCollector.c srcs/wsh_parsing/wsh_parse.c srcs/wsh_read.c
BSRCS = includes/
all : $(NAME)
$(NAME):
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $(flags) $(SRCS) -I $(BSRCS) -g $(LIBFT_DIR)/$(LIBFT_NAME) -fsanitize= -o $(NAME)

bonus:
	@$(CC) $(flags) -I $(BSRCS) $(LIBFT_DIR)/$(LIBFT_NAME) -o $(NAME)

clean: 
	@rm -rf $(LIBFT_DIR)/*.o

fclean: clean
	@rm -rf $(NAME) $(LIBFT_DIR)/$(LIBFT_NAME)

re: fclean all
	@echo "Rebuilding Library."