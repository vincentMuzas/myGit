CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -Wpedantic -O3 -march=native -I./
LDFLAGS	=

NAME	= myGit
SRC		= 	main.c	\
			usage.c	\
			init.c	\
			status.c

OBJ		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

exec: all
	@echo "========================================"
	@echo "Compilation and execution successful!"
	@echo "========================================"
	@echo ""
	@echo "===> running <==="
	./$(NAME)

launch: exec

e: exec

.PHONY: all clean fclean re exec launch e
