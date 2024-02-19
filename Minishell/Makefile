# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/24 15:20:25 by lpicciri          #+#    #+#              #
#    Updated: 2024/02/19 09:30:06 by mcamilli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT =	./libft/libft.a

ALL = minishell

SRCS = lexer/*.c mini_main/*.c

OBJS = ${SRCS:.c=.o}

CC = gcc

RM = rm -f

FLAGS = -Wall -Wextra -Werror

$(NAME): $(LIBFT) ${OBJS}
		${CC} ${FLAGS} -o ${NAME} $(LIBFT) ${OBJS} -lreadline

all: ${NAME}

$(LIBFT):
		make -C libft

clean:
		${RM} ${OBJS}
		make clean -C libft

fclean: clean
		${RM} ${NAME}
		${RM} ${LIBFT}

re: fclean all

.PHONY: all clean re
