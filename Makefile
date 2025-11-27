CC       = gcc
CFLAGS   = -Wall -Wextra -Werror
MLXFLAGS = -L/home/jobito/Cub3d/minilibx-linux -lmlx -lXext -lX11 -lm
SRC      = cub3d.c \
	   basic_utilities/basic_utils_0.c \
	   calculation_utilities/calc_utils_0.c calculation_utilities/calc_utils_1.c calculation_utilities/render.c \
	   drawing_utilities/draw_utils_0.c \
	   initialization_utilities/init_utils_0.c
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
