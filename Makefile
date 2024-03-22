# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kseniakaremina <kseniakaremina@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/17 14:30:39 by kseniakarem       #+#    #+#              #
#    Updated: 2024/03/22 11:59:29 by kseniakarem      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
NAME = philo
SRCS = philo.c 
OBJ = $(SRCS:.c=.o)

all:$(NAME)

$(NAME): $(OBJ)
	cc -o $(NAME) $(OBJ)

%.o: %.c
	cc $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all


.PHONY: all clean fclean re bonus