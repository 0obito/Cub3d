#ifndef HEADER
#define HEADER

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>

# define WIN_HEIGHT 500
# define WIN_WIDTH 500
# define MAP_HEIGHT 10
# define MAP_WIDTH 8
# define GRID_HEIGHT (WIN_HEIGHT / MAP_HEIGHT)
# define GRID_WIDTH (WIN_WIDTH / MAP_WIDTH)

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_mlx;

typedef struct s_imgdata
{
	void	*img_ptr;
	void	*img_add;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_imgdata;

typedef struct s_player_pos
{
	int		x;
	int		y;
}				t_player_pos;

typedef struct s_variables
{
	t_mlx			*mlx_vars;
	t_imgdata		*imgdata_vars;
	t_player_pos	*coordinates_vars;
}				t_variables;

#endif /* HEADER */
