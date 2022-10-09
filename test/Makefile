##
## EPITECH PROJECT, 2022
## test socket C
## File description:
## Makefile
##

SRC = $(wildcard src/*.c)

OBJ = $(SRC:.c=.o)

C_FLAGS = -Wall -Wextra -g -lncurses

NAME = socket_server

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(OBJ) -o $(NAME) $(C_FLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re