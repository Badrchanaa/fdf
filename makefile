#! /usr/bin/make

CC = cc
CFLAGS = -Wall -Wextra -Werror -O3
LIBFLAGS = -lmlx -framework openGL -framework Appkit -lft -L./libft
LINUX_FLAGS = -lft -L./libft -lmlx -L. -lXext -lX11 -lm -lz
LIB_INCLUDE = -I./
MY_INCLUDE = -I./include -I./libft
LIBDIR = ./
VPATH = src

SOURCES = color.c main.c init.c common_utils.c parser.c parse_utils.c draw_utils.c rot_utils.c transform_utils.c event_handlers.c misc.c bline.c
OBJECTS = $(SOURCES:.c=.o)
HEADERS = ./include/fdf.h

LIBFT_DIR = ./libft
LIBFT_NAME = $(addprefix $(LIBFT_DIR)/, libft.a)

NAME = fdf

all: $(NAME)

run:
	./$(NAME)

$(NAME): $(LIBFT_NAME) $(OBJECTS)
	$(CC) $(CFLAGS) $(LIB_INCLUDE) $(OBJECTS) -o $(NAME) $(LINUX_FLAGS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(MY_INCLUDE) -c $< -o $@

$(LIBFT_NAME):
	@echo $(LIBFT_NAME)
	make --directory $(LIBFT_DIR) bonus
	make --directory $(LIBFT_DIR) clean

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)
	make --directory $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all fclean clean re

