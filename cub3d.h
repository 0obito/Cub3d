/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:38:20 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/11/05 15:38:11 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* the header inclusions */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "./minilibx-linux/mlx.h"
# include <X11/keysym.h>

/* the MACROs */
# define WIN_HEIGHT 1000
# define WIN_WIDTH 1000
# define MAP_HEIGHT 10
# define MAP_WIDTH 10
# define GRID_HEIGHT (WIN_HEIGHT / MAP_HEIGHT)
# define GRID_WIDTH (WIN_WIDTH / MAP_WIDTH)

/* an enum for player directions */
typedef enum directions
{
	UP,
	DOWN,
	RIGHT,
	LEFT
}				t_direction;

/* a structure for window creation info */
typedef struct s_mlxdata
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_mlxdata;

/* a structure for image info */
typedef struct s_imgdata
{
	void	*img_ptr;
	void	*img_add;
	int		bpp;
	int		line_length;
	int		endian;
}				t_imgdata;

/* a structure for player info */
typedef struct s_playerdata
{
	double			x;
	double			y;
	char			direction;
	double			starting_angle;
}				t_playerdata;

typedef struct s_coord
{
	int	y;
	int	x;
}				t_coord;

typedef struct s_ray
{
	double	ray_length;
	double	ray_angle;
	double	grid_y;
	double	grid_x;
	double	nearest_blocky;
	double	nearest_blockx;
	double	traveled_y;
	double	traveled_x;
}				t_ray;

/* a structure that holds the important data to comfortably use it around */
typedef struct s_data
{
	t_mlxdata		*mlx;
	t_imgdata		*img;
	t_playerdata	*player;
	t_ray			*ray;
	unsigned int	ceiling_color;
	unsigned int	floor_color;
}				t_data;

/* Function Prototypes*/
int		initiate_mlx(t_data *data, t_mlxdata *mlx, t_imgdata *img);
int		initiate_player_and_ray(t_data *data, t_playerdata *player, t_ray *ray);
void	color_grid(t_data *data, int grid_x, int grid_y);
void	draw_a_line(t_data *data);
void	draw_direction_vector(t_data *data);
void	draw_player(t_data *data, int grid_x, int grid_y);
int		render(t_data *data, char map[MAP_HEIGHT][MAP_WIDTH]);
int		ft_strlen(const char *s);
int		ft_write(const char *s);

#endif /* CUB3D_H */
