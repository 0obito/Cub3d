CC       = gcc
CFLAGS   = -Wall -Wextra -Werror
MLXFLAGS = -lmlx -lXext -lX11 -lm
SRC      = cub3d.c utilities/utils_1.c Rendering/init.c Rendering/drawing_utils.c Rendering/render.c
OBJ      = $(SRC:.c=.o)
NAME     = Cub3d

$(NAME)  : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLXFLAGS) -o $(NAME)

all      : $(NAME)

clean    :
	rm -f $(OBJ)

fclean   : clean
	rm -f $(NAME)

re       : fclean $(NAME)

.PHONY: clean

.SECONDARY: $(OBJ)
