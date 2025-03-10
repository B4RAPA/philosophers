NAME = philosophers

CC = cc

CFLAGS = -Werror -Wextra -Wall -fsanitize=thread

INCLUDES = philosophers.h

SRCS = main.c\
		init.c\
		time.c\
		routine.c

OBJ = main.o\
		init.o\
		time.o\
		routine.o

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -I$(INCLUDES) -o $(NAME) $(OBJ)

clean:
		rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re