NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRC = main.c utils.c init.c actions.c monitor.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
