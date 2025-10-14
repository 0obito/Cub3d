#ifndef HEADER
#define HEADER

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>

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

typedef struct s_coordinates
{
	int		x;
	int		y;
}				t_coordinates;

typedef struct s_variables
{
	t_mlx			*mlx_vars;
	t_imgdata		*imgdata_vars;
	t_coordinates	*coordinates_vars;
}				t_variables;

#endif /* HEADER */
