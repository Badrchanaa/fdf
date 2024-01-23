#! /usr/bin/make

CC = cc
CFLAGS = -Wall -Wextra -Werror -O3
LIBS = -lmlx -framework openGL -framework Appkit -lft -L./libft
MLX_INCLUDE = -I /usr/local/include
FDF_INCLUDE = -I./include -I./libft
LIBDIR = /usr/local/lib
VPATH = src:objects

SOURCES = color.c main.c init.c common_utils.c parser.c parse_utils.c draw_utils.c rot_utils.c transform_utils.c event_handlers.c misc.c bline.c
OBJECTS_DIR = ./objects
OBJECTS = $(addprefix $(OBJECTS_DIR)/, $(SOURCES:.c=.o))
HEADERS = ./include/fdf.h

GREEN = \033[32m
BOLD = \033[1m
RESET = \033[0m

LIBFT_DIR = ./libft
LIBFT_NAME = $(addprefix $(LIBFT_DIR)/, libft.a)

NAME = fdf

all: $(NAME)

bonus: $(NAME)
	

$(NAME): $(LIBFT_NAME) $(OBJECTS)
	@$(CC) $(CFLAGS) $(MLX_INCLUDE) $(LIBS) -L $(LIBDIR) $(OBJECTS) -o $(NAME)
	@echo "$(GREEN)$(BOLD)$(NAME)$(RESET)$(GREEN) compiled successfuly!$(RESET)"

$(OBJECTS_DIR)/%.o: %.c $(HEADERS)
	@echo "$(GREEN)Compiling $(BOLD)$(NAME)$(RESET)$(GREEN) project...$(RESET)"
	$(CC) $(CFLAGS) $(FDF_INCLUDE) -c $< -o $@

$(LIBFT_NAME):
	@echo "$(GREEN)	Compiling $(BOLD)libft$(RESET)$(GREEN)...$(RESET)"
	@make --silent --directory $(LIBFT_DIR) bonus
	@make --silent --directory $(LIBFT_DIR) clean
	@echo "$(GREEN)	Libft compiled successfuly!$(RESET)"

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)
	make --directory $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all fclean clean re

