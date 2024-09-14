# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kseniakaremina <kseniakaremina@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/17 14:30:39 by kseniakarem       #+#    #+#              #
#    Updated: 2024/09/13 18:05:36 by kseniakarem      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
NAME = philo
SRCS = philo.c creating.c routine.c forks.c helpers.c
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


valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=definite --track-origins=yes ./$(NAME) 5 100 100 100 100

test: $(NAME)
	./$(NAME) 4 310 200 100

docker:
	docker build -t philo .
	docker run --rm -it philo 5 100 100 100 100

.PHONY: all clean fclean re bonus