# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gicomlan <gicomlan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/08 13:59:24 by gicomlan          #+#    #+#              #
#    Updated: 2025/05/08 13:59:30 by gicomlan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_donut

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lm

SRC = main.c \
      ft_donut_utils.c \
      ft_donut_init.c \
      ft_donut_math.c \
      ft_donut_render.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
