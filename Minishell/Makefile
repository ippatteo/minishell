# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    MAKEFILE                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpicciri <lpicciri@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/24 15:20:25 by lpicciri          #+#    #+#              #
#    Updated: 2024/01/24 15:54:17 by lpicciri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT =	./libft/libft.a

ALL = minishell

SRCS = lexer.c minishell.c

OBJS = ${SRCS:.c=.o}

CC = gcc

RM = rm -f

FLAGS = -Wall -Wextra -Werror

$(NAME): $(LIBFT) ${OBJS}
		${CC} ${FLAGS} -o ${NAME} $(LIBFT) ${OBJS} -lreadline

all: ${NAME}

$(LIBFT):
		make -C ./libft

clean:
		${RM} ${OBJS}
		make clean -C ./libft

fclean: clean
		${RM} ${NAME}
		${RM} ${LIBFT}

re: fclean all

.PHONY: all clean re
