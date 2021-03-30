# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mashad <mashad@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/17 12:48:00 by mashad            #+#    #+#              #
#    Updated: 2021/01/06 08:54:16 by mashad           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
AR = ar
NAME = libft.a
flags = -Wall -Wextra -Werror
SRCS = ft_substr.c ft_isin.c ft_strjoin.c ft_split.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memchr.c ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_isprint.c ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c ft_calloc.c
all : $(NAME)
$(NAME):
	@$(CC) $(flags) -c $(SRCS)
	@$(AR) rsc $(NAME) *.o

bonus:
	@$(CC) $(flags) -c $(BSRCS)
	@$(AR) rc $(NAME) *.o

clean: 
	@rm -rf *.o

fclean: clean
	@rm -rf *.a

re: fclean all
	@echo "Rebuilding Library."
