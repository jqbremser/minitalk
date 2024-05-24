# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    MAKEFILE                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbremser <jbremser@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/21 14:18:10 by jbremser          #+#    #+#              #
#    Updated: 2024/05/24 15:24:29 by jbremser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
CLIENT_SRCS = client.c
SERVER_SRCS = server.c
CLIENT_BONUS_SRCS = client_bonus.c
SERVER_BONUS_SRCS = server_bonus.c
LIBFT_PATH = libft
LIBFT_ARCHIVE = $(LIBFT_PATH)/libft.a
CLIENT_NAME = client
SERVER_NAME = server
CLIENT_BONUS_NAME = client_bonus
SERVER_BONUS_NAME = server_bonus

# Directories for object files
OBJ_DIR = obj
BONUS_OBJ_DIR = bonus_obj

# Derived object files
CLIENT_OBJS = $(OBJ_DIR)/client.o
SERVER_OBJS = $(OBJ_DIR)/server.o
CLIENT_BONUS_OBJS = $(BONUS_OBJ_DIR)/client_bonus.o
SERVER_BONUS_OBJS = $(BONUS_OBJ_DIR)/server_bonus.o

all: $(CLIENT_NAME) $(SERVER_NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BONUS_OBJ_DIR):
	mkdir -p $(BONUS_OBJ_DIR)

$(CLIENT_NAME): $(OBJ_DIR) $(CLIENT_OBJS) $(LIBFT_ARCHIVE)
	$(CC) $(CFLAGS) -o $@ $(CLIENT_OBJS) -L$(LIBFT_PATH) -lft

$(SERVER_NAME): $(OBJ_DIR) $(SERVER_OBJS) $(LIBFT_ARCHIVE)
	$(CC) $(CFLAGS) -o $@ $(SERVER_OBJS) -L$(LIBFT_PATH) -lft

$(CLIENT_BONUS_NAME): $(BONUS_OBJ_DIR) $(CLIENT_BONUS_OBJS) $(LIBFT_ARCHIVE)
	$(CC) $(CFLAGS) -o $@ $(CLIENT_BONUS_OBJS) -L$(LIBFT_PATH) -lft

$(SERVER_BONUS_NAME): $(BONUS_OBJ_DIR) $(SERVER_BONUS_OBJS) $(LIBFT_ARCHIVE)
	$(CC) $(CFLAGS) -o $@ $(SERVER_BONUS_OBJS) -L$(LIBFT_PATH) -lft

$(LIBFT_ARCHIVE):
	$(MAKE) -C $(LIBFT_PATH)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BONUS_OBJ_DIR)/%.o: %.c | $(BONUS_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	rm -rf $(OBJ_DIR) $(BONUS_OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	rm -f $(CLIENT_NAME) $(SERVER_NAME) $(CLIENT_BONUS_NAME) $(SERVER_BONUS_NAME)

re: fclean all

bonus: $(CLIENT_BONUS_NAME) $(SERVER_BONUS_NAME)

.PHONY: all clean fclean re bonus
