# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wtang <wtang@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/12 23:24:22 by wtang             #+#    #+#              #
#    Updated: 2025/08/27 00:43:09 by wtang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
CC = gcc
CFLAGS = -Wall -Wextra -Werror

LIBFT = libft/libft.a
MLX_LINUX = mlx_linux/libmlx_Linux.a

INCLUDES = -Ilibft -Imlx_linux -Isrc

LDFLAGS = -Llibft -Lmlx_linux
LDLIBS = -lft -lmlx_Linux -lm -lX11 -lXext

SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:.c=.o)

RM = rm -f

MLX_FLAGS = -O3

all: $(LIBFT) $(MLX_LINUX) $(NAME)

$(LIBFT):
	make -C libft

$(MLX_LINUX):
	make -C mlx_linux $(MLX_FLAGS)

$(NAME): $(OBJ) $(LIBFT) $(MLX_LINUX)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJ)
	make -C libft clean
	make -C mlx_linux clean

fclean: clean
	$(RM) $(NAME)
	make -C libft fclean
	make -C mlx_linux clean

re: fclean all

.PHONY: all clean fclean re