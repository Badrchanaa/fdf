CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFLAGS = -lmlx -framework openGL -framework Appkit -lft -L./libft
LIB_INCLUDE = -I /usr/local/include
MY_INCLUDE = -I./include -I./libft -I/usr/local/include
LIBDIR = /usr/local/lib

SOURCES = main.c init.c common_utils.c parser.c parse_utils.c draw_utils.c translate.c rot_utils.c transform_utils.c
OBJECTS = $(SOURCES:.c=.o)

NAME = fdf

all: $(NAME)

run:
	./$(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(LIB_INCLUDE) $(LIBFLAGS) -L $(LIBDIR) $(OBJECTS) -o $(NAME) -g -fsanitize=address

%.o: %.c
	$(CC) $(CFLAGS) $(MY_INCLUDE) -c $? -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all fclean clean re

