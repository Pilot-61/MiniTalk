# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 23:05:57 by mes-salh          #+#    #+#              #
#    Updated: 2024/02/25 01:03:27 by mes-salh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk

SRC_CLIENT = client.c utils.c
SRC_SERVER = server.c utils.c
SRC_CLIENT_BONUS = client_bonus.c utils.c
SRC_SERVER_BONUS = server_bonus.c utils.c

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT_BONUS = $(SRC_CLIENT_BONUS:.c=.o)
OBJ_SERVER_BONUS = $(SRC_SERVER_BONUS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): client server

bonus: client_bonus server_bonus

client: $(OBJ_CLIENT)
	$(CC) $(CFLAGS) -o client $(OBJ_CLIENT)

server: $(OBJ_SERVER)
	$(CC) $(CFLAGS) -o server $(OBJ_SERVER)

client_bonus: $(OBJ_CLIENT_BONUS)
	$(CC) $(CFLAGS) -o client_bonus $(OBJ_CLIENT_BONUS)

server_bonus: $(OBJ_SERVER_BONUS)
	$(CC) $(CFLAGS) -o server_bonus $(OBJ_SERVER_BONUS)

%.o: %.c minitalk.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_CLIENT) $(OBJ_SERVER) $(OBJ_CLIENT_BONUS) $(OBJ_SERVER_BONUS)

fclean: clean
	rm -f client server client_bonus server_bonus

re: fclean all
