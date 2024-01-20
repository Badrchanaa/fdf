CC = cc
CFLAGS = -Wall -Wextra -Werror -O3
LIBFLAGS = -lmlx -framework openGL -framework Appkit -lft -L./libft
LIB_INCLUDE = -I /usr/local/include
MY_INCLUDE = -I./include -I./libft
LIBDIR = /usr/local/lib

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
	$(CC) $(CFLAGS) $(LIB_INCLUDE) $(LIBFLAGS) -L $(LIBDIR) $(OBJECTS) -o $(NAME) 

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

