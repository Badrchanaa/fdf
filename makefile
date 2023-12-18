CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFLAGS = -lmlx -framework openGL -framework Appkit -lft -L./libft
LIB_INCLUDE = -I /usr/local/include
MY_INCLUDE = -I./include -I./libft
LIBDIR = /usr/local/lib

SOURCES = main.c
OBJECTS = $(SOURCES:.c=.o)

NAME = fdf

all: $(NAME)

run:
	./$(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(LIB_INCLUDE) $(LIBFLAGS) -L $(LIBDIR) $(OBJECTS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(MY_INCLUDE) -c $? -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all fclean clean re

