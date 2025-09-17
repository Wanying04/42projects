# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/12 23:24:22 by wtang             #+#    #+#              #
#    Updated: 2025/09/15 16:47:48 by wtang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT = lib/libft/libft.a
MLX_LINUX = lib/mlx_linux/libmlx_Linux.a

INCLUDES = -Ilib/libft -Ilib/mlx_linux -Isrc
LDFLAGS = -Llib/libft -Llib/mlx_linux
LDLIBS = -lft -lmlx_Linux -lm -lX11 -lXext

SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:.c=.o)

RM = rm -f

all: $(LIBFT) $(MLX_LINUX) $(NAME)

$(LIBFT):
	make -C lib/libft

$(MLX_LINUX):
	make -C lib/mlx_linux

$(NAME): $(OBJ) $(LIBFT) $(MLX_LINUX)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJ)
	make -C lib/libft clean
	make -C lib/mlx_linux clean

fclean: clean
	$(RM) $(NAME)
	make -C lib/libft fclean
	make -C lib/mlx_linux clean

re: fclean all

.PHONY: all clean fclean re