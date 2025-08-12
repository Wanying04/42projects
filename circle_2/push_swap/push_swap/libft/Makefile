# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/02 15:19:02 by wtang             #+#    #+#              #
#    Updated: 2024/12/19 18:37:04 by wtang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra

# Define source files for the main part and bonus part
SRCS = ft_isdigit.c ft_atoi.c ft_split.c

# Object files for both main and bonus parts
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

RM = rm -f

# Default target to build the library
all: $(NAME)

# Rule to create the static library from object files
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

# Bonus target to create the library with bonus object files
bonus: $(BONUS_OBJS)
	ar rcs $(NAME) $(BONUS_OBJS)

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files
clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

# Clean and remove the library
fclean: clean
	$(RM) $(NAME)

# Rebuild everything from scratch
re: fclean all

# Declare non-file targets
.PHONY: all clean fclean re bonus
