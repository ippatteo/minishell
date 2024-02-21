# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/24 15:20:25 by lpicciri          #+#    #+#              #
#    Updated: 2024/02/21 15:45:37 by mcamilli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT =	libft

ALL = minishell

SRCS = lexer/*.c mini_main/*.c

#OBJS = ${SRCS:.c=.o}

CC = gcc

RM = rm -f

FLAGS = -Wall -Wextra -Werror


all: 
	make -C $(LIBFT)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT)/libft.a -o $(NAME) -lreadline

clean:
		${RM} ${OBJS}
		make clean -C libft

fclean: clean
		${RM} ${NAME}
		${RM} ${LIBFT}

re: fclean all

.PHONY: all clean re
