##
## EPITECH PROJECT, 2022
## test socket C
## File description:
## Makefile
##

SRC = 	$(wildcard src/*.c)	\
		$(wildcard src/*/*.c)	\
		$(wildcard src/*/*/*.c)

OBJ = $(SRC:.c=.o)

C_FLAGS = -Wall -Wextra -g -lncurses #-lpthread

CSFML_FLAGS = -lcsfml-system -lcsfml-graphics -lcsfml-window -lcsfml-audio -lcsfml-network -lm

NAME = rpg_server

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(OBJ) -o $(NAME) -iquote include/ $(C_FLAGS) $(CSFML_FLAGS)
	mv $(NAME) ../

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f ../$(NAME)

re: fclean all

.PHONY: all clean fclean re