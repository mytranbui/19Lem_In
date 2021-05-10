# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbui <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/15 17:37:13 by mbui              #+#    #+#              #
#    Updated: 2021/04/08 18:47:40 by mbui             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
CC = gcc
FLG = -Wall -Wextra -Werror #-fsanitize=address
SRC_DIR = src/
SRC = main.c utils.c algo.c#parse.c algo.c algo2.c 
LIB = libft/libft.a
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): getlibft
	@$(CC) $(FLG) -c $(addprefix $(SRC_DIR)/,$(SRC))
	@$(CC) $(FLG) $(OBJ) $(LIB) -o $(NAME)
	@echo "\033[1;32m$(NAME) \033[0m\033[32mcreated.\033[0m"

getlibft:
	@make -C libft

clean:
	@rm -f $(OBJ)
	@make clean -C libft
	@echo "\033[31mobject files of \033[0m\033[1;31m$(NAME)\033[0m \033[31mremoved.\033[0m"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft
	@echo "\033[1;31m$(NAME) \033[0m\033[31mremoved.\033[0m"

re: fclean all

.PHONY: clean fclean all re
