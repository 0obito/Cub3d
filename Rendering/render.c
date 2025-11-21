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

void	draw_wall(t_data *data, int ray_num, double corr_angle)
{
	char	*dst;
	int		counter;
	double	wall_height;
	t_coord	params;

	data->ray->ray_length *= cos(corr_angle * (M_PI / 180));
	wall_height = WIN_HEIGHT * (100 / (data->ray->ray_length
					* cos(corr_angle * (M_PI / 180))));
	// printf("Ray length is %f\n", data->ray->ray_length);
	// printf("Corr angle is %f\n", corr_angle);
	// printf("Wall height is %f\n\n", wall_height);
	params.y = (WIN_HEIGHT / 2) - (wall_height / 2);
	params.x = ray_num * (WIN_WIDTH / 200);
	while (wall_height > 0)
	{
		counter = 1;
		while (counter < 4)
		{
			dst = data->img->img_add + ((int)params.y * data->img->line_length)
				+ (((int)params.x + counter) * (data->img->bpp / 8));
			*(unsigned int *)dst = 0xFF0000FF;
			counter += 1;
		}
		params.y += 1;
		wall_height -= 1;
	}
}

void	values_corrector(t_data *data, double angle)
{
	(void)((angle >= 0) && (angle < 90)
		&& (data->ray->y_corr = -1) && (data->ray->x_corr = 1));
	(void)((angle >= 90) && (angle < 180)
		&& (data->ray->y_corr = -1) && (data->ray->x_corr = -1));
	(void)((angle >= 180) && (angle < 270)
		&& (data->ray->y_corr = 1) && (data->ray->x_corr = -1));
	(void)((angle >= 270) && (angle < 360)
		&& (data->ray->y_corr = 1) && (data->ray->x_corr = 1));
}

	// notice: there's a division by 0 possibility

void	next_grid_finder(t_data *data, double *nearest_y, double *nearest_x, char *last_met)
{
	if (*nearest_y < *nearest_x)
	{
		*last_met = 'y';
		data->ray->grid_y += data->ray->y_corr;
		*nearest_y += data->ray->nearest_blocky;
	}
	else if (*nearest_y > *nearest_x)
	{
		*last_met = 'x';
		data->ray->grid_x += data->ray->x_corr;
		*nearest_x += data->ray->nearest_blockx;
	}
	else
	{
		*last_met = 'b';
		data->ray->grid_y += data->ray->y_corr;
		data->ray->grid_x += data->ray->x_corr;
		*nearest_y += data->ray->nearest_blocky;
		*nearest_x += data->ray->nearest_blockx;
	}
	return ;
}

double	find_wall(t_data *data, double angle, char map[MAP_HEIGHT][MAP_WIDTH])
{
	double	nearest_y;
	double	nearest_x;
	char	last_met;

	values_corrector(data, angle);
	data->ray->grid_y = data->player->grid_y;
	data->ray->grid_x = data->player->grid_x;
	nearest_y = data->ray->nearest_blocky;
	nearest_x = data->ray->nearest_blockx;
	while (data->ray->grid_y >= 0 && data->ray->grid_y <= 9
			&& data->ray->grid_x >= 0 && data->ray->grid_x <= 9)
	{
		next_grid_finder(data, &nearest_y, &nearest_x, &last_met);
		if (map[data->ray->grid_y][data->ray->grid_x] == '1')
		{
			if (last_met == 'y')
				return (((nearest_y  - (3 / 2) * data->ray->nearest_blocky))
					/ fabs(sin(angle * (M_PI / 180))));
			else
				return ((nearest_x  - (3 / 2) * data->ray->nearest_blockx)
				/ fabs(cos(angle * (M_PI / 180))));
		}
	}
	return (0);
}

/* a function that cast the rays */
void	ray_caster(t_data *data, char map[MAP_HEIGHT][MAP_WIDTH])
{
	int			ray_num;
	double		angle;
	double		delta_angle;
	double		correction_angle;

	delta_angle = 60;
	angle = (data->player->starting_angle) - (delta_angle / 2) + 360;
	data->ray->ray_length = 0;
	ray_num = -1;
	correction_angle = (delta_angle / 2);
	while (++ray_num < 200)
	{
		angle = fmod(angle, 360);
		data->ray->nearest_blocky
			= fabs(GRID_HEIGHT / (sin(angle * (M_PI / 180))));
		data->ray->nearest_blockx
			= fabs(GRID_WIDTH / (cos(angle * (M_PI / 180))));
		data->ray->ray_length = find_wall(data, angle, map);
		draw_wall(data, ray_num, correction_angle);
		angle += 0.3000000000;
		correction_angle -= 0.3;
	}
}

void	block_to_pixel_coords(t_data *data, int j, int i)
{
	data->player->y = (j + 1 / 2) * (WIN_HEIGHT / MAP_HEIGHT);
	data->player->x = (i + 1 / 2) * (WIN_WIDTH / MAP_WIDTH);
	data->player->grid_y = j;
	data->player->grid_x = i;
	(void)((data->player->direction == 'N') && (data->player->starting_angle = 90));
	(void)((data->player->direction == 'S') && (data->player->starting_angle = 270));
	(void)((data->player->direction == 'E') && (data->player->starting_angle = 0));
	(void)((data->player->direction == 'W') && (data->player->starting_angle = 180));
	printf("Player's map coordinates are: y:%d and x:%d\n", j, i);
}

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
	char			*dst;
	unsigned int	color;
	int				y;
	int				x;

	color = 0xFF663300;
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		(void)((y == (WIN_HEIGHT / 2)) && (color = 0xFF1B1C1D) && printf("color set\n"));
		x = -1;
		while (++x < WIN_WIDTH)
		{
			dst = data->img->img_add + (y * data->img->line_length)
				+ (x * (data->img->bpp / 8));
			*(unsigned int *)dst = color;
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
