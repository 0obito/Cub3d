CC       = gcc
CFLAGS   = -Wall -Wextra -Werror
MLXFLAGS = -lmlx -lXext -lX11
SRC      = Rendering/first_step.c
OBJ      = $(SRC:.c=.o)
NAME     = Cub3d

$(NAME)  : $(OBJ)
	$(CC) -fsanitize=address $(CFLAGS) $(OBJ) $(MLXFLAGS) -o $(NAME)

all      : $(NAME)

clean    :
	rm -f $(OBJ)

fclean   : clean
	rm -f $(NAME)

re       : fclean $(NAME)

.PHONY: clean

.SECONDARY: $(OBJ)
