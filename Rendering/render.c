/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:09:48 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/11/05 16:12:22 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_wall(t_data *data, int ray_num)
{
	char	*dst;
	double	wall_height;
	double	delta_py;
	double	delta_px;

	// ray_num (0 -> 99 included)
	printf("Ray length: %f\n", data->ray->ray_length);
	wall_height = WIN_HEIGHT - data->ray->ray_length;
	printf("Wall height: %f\n", wall_height);
	delta_py = (WIN_HEIGHT / 2) - (wall_height / 2);
	printf("Delta py: %f\n", delta_py);
	delta_px = WIN_WIDTH / 100;
	printf("Delta px: %f\n", delta_px);
	while (wall_height > 0)
	{
		dst = (data->img->img_add) + ((int)(delta_py * data->img->line_length))
			+ ((int)((delta_px + ray_num) * (data->img->bpp / 8)));
		*dst = 200;
		// dst = 200;
		delta_py += 1;
		wall_height -= 1;
	}
}

void	values_corrector(int *y_corr, int *x_corr, double angle)
{
	(void)((angle >= 0) && (angle <= 90)
		&& (*y_corr = 1) && (*x_corr = 1) && printf("quart 1\n"));
	(void)((angle >= 90) && (angle <= 180)
		&& (*y_corr = 1) && (*x_corr = -1) && printf("quart 2\n"));
	(void)((angle >= 180) && (angle <= 270)
		&& (*y_corr = -1) && (*x_corr = -1) && printf("quart 3\n"));
	(void)((angle >= 270) && (angle <= 360)
		&& (*y_corr = -1) && (*x_corr = 1) && printf("quart 4\n"));
}

	// notice: there's a division by 0 possibility
double	find_wall(t_data *data, double angle, char map[MAP_HEIGHT][MAP_WIDTH])
{
	double	nearest_y;
	double	nearest_x;
	int		grid_y;
	int		grid_x;
	int		y_corr;
	int		x_corr;
	int		last_met;

	values_corrector(&y_corr, &x_corr, angle);
	printf("Ray at angle: %f\n", angle);
	nearest_y = data->ray->nearest_blocky;
	nearest_x = data->ray->nearest_blockx;
	grid_y = data->ray->grid_y;
	grid_x = data->ray->grid_x;
	while (grid_y >= 0 && grid_y <= 9 && grid_x >= 0 && grid_x <= 9)
	{
		if (nearest_y < nearest_x)
		{
			last_met = 1;
			grid_y += y_corr;
			nearest_y += data->ray->nearest_blocky;
		}
		else if (nearest_y > nearest_x)
		{
			last_met = 0;
			grid_x += x_corr;
			nearest_x += data->ray->nearest_blockx;
		}
		else
		{
			last_met = 2;
			grid_y += y_corr;
			grid_x += x_corr;
			nearest_y += data->ray->nearest_blocky;
			nearest_x += data->ray->nearest_blockx;
		}
		if (grid_y >= 0 && grid_y <= 9 && grid_x >= 0 && grid_x <= 9
				&& map[grid_y][grid_x] == '1')
		{
			printf("Wall found at %d %d\n", grid_y, grid_x);
			printf("delta y: %f\n", data->ray->nearest_blocky);
			printf("y final: %f\n", nearest_y);
			printf("delta x: %f\n", data->ray->nearest_blockx);
			printf("x final: %f\n", nearest_x);
			if (!last_met)
				return (((nearest_y  - ((2 / 2) * data->ray->nearest_blocky))) / (sin(angle * (M_PI / 180))));
			else
				return (((nearest_x  - ((2 / 2) * data->ray->nearest_blockx))) / (cos(angle * (M_PI / 180))));
		}
	}
	return (0);
}

void	cast_vectors(t_data *data, char map[MAP_HEIGHT][MAP_WIDTH])
{
	double		angle;
	double		delta_angle;
	double		ray_len;
	int			ray_num;

	delta_angle = 30;
	angle = (data->player->starting_angle) - (delta_angle / 2) + 360;
	data->ray->ray_length = 0;
	data->ray->traveled_y = GRID_HEIGHT / 2;
	data->ray->traveled_x = GRID_WIDTH / 2;
	ray_num = 0;
	while (ray_num < 100)
	{
		// set to half the value at first (player is in the center of the grid)
		// then start resetting it to the whole value everytime
		// the corresponding grid is encountered.
		angle = (int)angle % 360;
		data->ray->nearest_blocky
			= fabs(GRID_HEIGHT / (sin(angle * (M_PI / 180))));
		data->ray->nearest_blockx
			= fabs(GRID_WIDTH / (cos(angle * (M_PI / 180))));
		ray_len = find_wall(data, angle, map);
		printf("ray_length original from func: %f\n", ray_len);
		data->ray->ray_length = ray_len;
		draw_wall(data, ray_num);
		angle += 0.3000000000;
		ray_num += 1;
	}
}

/* a function that cast the rays */
void	ray_caster(t_data *data, char map[MAP_HEIGHT][MAP_WIDTH])
{
	// int	py;
	// int	px;

	// py = data->player->y;
	// px = data->player->x;
	cast_vectors(data, map);
}

void	block_to_pixel_coords(t_data *data, int j, int i)
{
	data->player->y = (j + 1 / 2) * (WIN_HEIGHT / MAP_HEIGHT);
	data->player->x = (i + 1 / 2) * (WIN_WIDTH / MAP_WIDTH);
	data->ray->grid_y = j;
	data->ray->grid_x = i;
	(void)((data->player->direction == 'N') && (data->player->starting_angle = 90));
	(void)((data->player->direction == 'S') && (data->player->starting_angle = 270));
	(void)((data->player->direction == 'E') && (data->player->starting_angle = 0));
	(void)((data->player->direction == 'W') && (data->player->starting_angle = 180));
	printf("Player's map coordinates are: y:%d and x:%d\n", j, i);
}

/* we're gonna have an i and j that represent the block we on when looking for the walls, just to make sure we dont go out of bounds. */
/*  */
void	find_player_grid(t_data *data, char map[MAP_HEIGHT][MAP_WIDTH])
{
	int		j;
	int		i;

	j = 0;
	while (j < 10)
	{
		i = 0;
		while (i < 10)
		{
			if ((map[j][i] == 'N') || (map[j][i] == 'S')
				|| (map[j][i] == 'E') || (map[j][i] == 'W'))
			{
				data->player->direction = map[j][i];
				printf("Found player in %c starting direction\n", map[j][i]);
				block_to_pixel_coords(data, j, i);
				return ;
			}
			i++;
		}
		j++;
	}
	ft_write("Player not found on the map!\n");
}

/* a function that colors the ceiling and the floor inside the window */
int	draw_ceiling_and_floor(t_data *data)
{
	char	*dst;
	int		y;
	int		x;

	y = -1;
	while (++y < WIN_HEIGHT / 2)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			dst = data->img->img_add + (y * data->img->line_length)
				+ (x * (data->img->bpp / 8));
			*(unsigned int *)dst = 0x663300;
		}
	}
	--y;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			dst = data->img->img_add + (y * data->img->line_length)
				+ (x * (data->img->bpp / 8));
			*(unsigned int *)dst = 0x1B1C1D;
		}
	}
	return (0);
}


/* the function that starts everything rendering wise */
int	render(t_data *data, char map[MAP_HEIGHT][MAP_WIDTH])
{
	find_player_grid(data, map);
	if (data->player->y < 0 || data->player->x < 0)
		return (1);
	draw_ceiling_and_floor(data);
	ray_caster(data, map);
	return (0);
}
