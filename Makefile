C = gcc
AR = ar
LIBFT_DIR = libft
LIBFT_NAME = libft.a
MAKE = make
NAME = minishell
flags = -Wall -Wextra -Werror
SRCS = srcs/minishell.c srcs/wsh_parsing/wsh_redirection_norm.c srcs/wsh_builtin.c srcs/wsh_parsing/wsh_parsing_norm.c srcs/wsh_parsing/wsh_all_tools.c srcs/wsh_parsing/wsh_redirection.c srcs/wsh_exec.c srcs/termcap/term_history.c srcs/wsh_garbageCollector.c srcs/wsh_parsing/wsh_parse.c srcs/wsh_parsing/wsh_parse_utils.c srcs/wsh_read.c srcs/built_ins/wsh_cd.c srcs/built_ins/wsh_echo.c srcs/built_ins/wsh_env.c srcs/built_ins/wsh_exit.c srcs/built_ins/wsh_export.c srcs/built_ins/wsh_pwd.c srcs/built_ins/wsh_unset.c srcs/wsh_exec_cmd.c srcs/wsh_exec_tools.c srcs/termcap/term_handlers.c srcs/termcap/term_inits.c srcs/termcap/termcap_tools.c srcs/built_ins/wsh_export_tools.c srcs/wsh_helper.c srcs/wsh_exec_cmd_norm.c srcs/wsh_exec_cmd_helper.c srcs/termcap/term_tools.c srcs/wsh_read_help.c
BSRCS = includes/
all : $(NAME)
$(NAME):
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $(flags) $(SRCS) -I $(BSRCS) -ltermcap $(LIBFT_DIR)/$(LIBFT_NAME) -o $(NAME)

bonus:
	@$(CC) $(flags) -I $(BSRCS) $(LIBFT_DIR)/$(LIBFT_NAME) -o $(NAME)

run: re
	@./$(NAME)
clean: 
	@rm -rf $(LIBFT_DIR)/*.o

fclean: clean
	@rm -rf $(NAME) $(LIBFT_DIR)/$(LIBFT_NAME)

re: fclean all
	@echo "Rebuilding Library."
