# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luca <luca@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/24 15:20:25 by lpicciri          #+#    #+#              #
#    Updated: 2024/04/09 19:19:58 by luca             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

MAIN_PATH = mini/
LEXER_PATH = lexer/
TOKEN_PATH = tokenizer/
EXEC_PATH = exec/
BUILTINS_PATH = builtins/
LIBFT_PATH = libft/
LIBFT = $(LIBFT_PATH)libft.a

SOURCE = $(wildcard $(MAIN_PATH)*.c) \
		 $(wildcard $(LEXER_PATH)*.c) \
		 $(wildcard $(TOKEN_PATH)*.c) \
		 $(wildcard $(EXEC_PATH)*.c) \
		 $(wildcard $(BUILTINS_PATH)*.c) \

OBJECTS = $(SOURCE:.c=.o)

CC = gcc

RM = rm -f

FLAGS = -Wall -Wextra -Werror -g

.o:.c
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJECTS)
	make -s -C $(LIBFT_PATH)
	$(CC) $(FLAGS) $(OBJECTS) $(LIBFT) -lreadline -o minishell

all: $(NAME)

clean:
	${RM} ${OBJECTS}
	rm -f minishell

fclean: clean
	make -s fclean -C ${LIBFT_PATH}

re: fclean all

.PHONY: all clean re
