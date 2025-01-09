# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dancel <dancel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/17 14:56:55 by dancel            #+#    #+#              #
#    Updated: 2024/11/17 17:10:47 by dancel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER = server
CLIENT = client
SERVER_BONUS = server_bonus
CLIENT_BONUS = client_bonus

CFLAGS = -Wall -Werror -Wextra
CC = cc
FLAGS = -Wall -Wextra -Werror -I$(PRINTF) -L$(PRINTF) -lftprintf

PRINTF = ft_printf
LIBFTPRINTF = $(PRINTF)/libftprintf.a
INCLUDES = -I$(PRINTF)

all: $(SERVER) $(CLIENT)

$(SERVER): server.c
	@make -s -C $(PRINTF)
	$(CC) $(CFLAGS) $(INCLUDES) server.c $(LIBFTPRINTF) -o $(SERVER)

$(CLIENT): client.c
	@make -s -C $(PRINTF)
	$(CC) $(CFLAGS) $(INCLUDES) client.c $(LIBFTPRINTF) -o $(CLIENT)

bonus: $(SERVER_BONUS) $(CLIENT_BONUS)

$(SERVER_BONUS): server_bonus.c $(LIBFTPRINTF)
	$(CC) $(CFLAGS) -I$(PRINTF) server_bonus.c $(LIBFTPRINTF) -o $(SERVER_BONUS)

$(CLIENT_BONUS): client_bonus.c $(LIBFTPRINTF)
	$(CC) $(CFLAGS) -I$(PRINTF) client_bonus.c $(LIBFTPRINTF) -o $(CLIENT_BONUS)

$(LIBFTPRINTF):
	$(MAKE) -C $(PRINTF)
	
clean:
	@make clean -s -C $(PRINTF)

fclean: clean
	@make fclean -s -C $(PRINTF)
	@rm -f $(SERVER) $(CLIENT) $(SERVER_BONUS) $(CLIENT_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
