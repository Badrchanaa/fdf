#! /usr/bin/make

CC = cc
CFLAGS = -Wall -Wextra -Werror -O3
LIBS = -lft -L./libft -lmlx -L. -lXext -lX11 -lm -lz
INCLUDE = -I./include -I./libft
LIBDIR = ./
VPATH = src

SOURCES = color.c main.c init.c common_utils.c parser.c parse_utils.c draw_utils.c rot_utils.c transform_utils.c event_handlers.c misc.c bline.c
OBJECTS = $(SOURCES:.c=.o)
HEADERS = ./include/fdf.h

GREEN = \033[32m

RESET = \033[0m

LIBFT_DIR = ./libft
LIBFT_NAME = $(addprefix $(LIBFT_DIR)/, libft.a)

NAME = fdf

all: $(NAME)

run:
	./$(NAME)

$(NAME): $(LIBFT_NAME) $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJECTS) -o $(NAME) $(LIBS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(LIBFT_NAME):
	@echo -e "$(GREEN)Compiling libft...$(RESET)"
	@make --directory $(LIBFT_DIR) bonus
	@make --directory $(LIBFT_DIR) clean
	@echo -e "$(GREEN)Libft compiled successfully$(RESET)"

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)
	make --directory $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all fclean clean re

