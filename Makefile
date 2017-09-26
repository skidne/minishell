# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgore <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/28 17:00:24 by pgore             #+#    #+#              #
#    Updated: 2017/02/03 14:15:27 by pgore            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc -Wall -Wextra -Werror
INC = -I ./includes/
LBFT = libft
SRC = src/*.c #pinacand wildcart

all: $(NAME)

$(NAME):
	make -C libft
	$(CC) $(SRC) $(INC) -L$(LBFT) -lft -o $(NAME)

test:	
	gcc $(SRC) $(INC) -L$(LBFT) -lft -o $(NAME)
clean:
	make clean -C libft

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
