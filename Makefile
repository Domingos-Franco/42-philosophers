# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgermano <dgermano@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/22 10:46:10 by dgermano          #+#    #+#              #
#    Updated: 2024/10/04 12:51:12 by dgermano         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC = $(NAME).c ft_atoui.c live_philopher.c
CC = cc
FLAGS = -Wall -Wextra -Werror -Wuninitialized
MSG = "\033[1m\033[32m$(NAME) Compiled\033[0m"
DEL = rm -f
OBJS = $(SRC:%.c=%.o)

all : $(NAME)
	@echo -e $(MSG)

$(NAME) : $(OBJS)
	@$(CC) -g $(FLAGS) $(OBJS) -lpthread -o $@

%.o:%.c
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@$(DEL) $(OBJS)

fclean: clean
	@$(DEL) $(NAME)

re: fclean all

.PHONY: all clean fclean re
