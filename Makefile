##
## EPITECH PROJECT, 2022
## test socket C
## File description:
## Makefile
##

NAME = prject

all: $(NAME)

$(NAME):
	make -C client_part
	make -C server_part

clean:
	make -C client_part clean
	make -C server_part clean

fclean: clean
	make -C client_part fclean
	make -C server_part fclean

re: fclean all

.PHONY: all clean fclean re