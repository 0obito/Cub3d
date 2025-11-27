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

void	next_grid_finder(t_data *data, double *nearest_y, double *nearest_x, char *last_met)
{
	if (*nearest_y < *nearest_x)
	{
		*last_met = 'y';
		data->ray->grid_y += data->ray->y_dir;
		*nearest_y += data->ray->nearest_blocky;
	}
	else if (*nearest_y > *nearest_x)
	{
		*last_met = 'x';
		data->ray->grid_x += data->ray->x_dir;
		*nearest_x += data->ray->nearest_blockx;
	}
	else
	{
		*last_met = 'b';
		data->ray->grid_y += data->ray->y_dir;
		data->ray->grid_x += data->ray->x_dir;
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
	double		correction_angle;

	angle = (data->player->starting_angle) - (FOV / 2) + 360;
	rad_to_deg(&angle);
	data->ray->ray_length = 0;
	ray_num = 0;
	correction_angle = (FOV / 2);
	deg_to_rad(&correction_angle);
	while (ray_num < NUM_OF_RAYS)
	{
		angle
		data->ray->nearest_blocky
			= fabs(GRID_HEIGHT / (sin(angle * (M_PI / 180))));
		data->ray->nearest_blockx
			= fabs(GRID_WIDTH / (cos(angle * (M_PI / 180))));
		data->ray->ray_length = find_wall(data, angle, map);
		draw_wall(data, ray_num, correction_angle);
		angle += 0.3000000000;
		correction_angle -= 0.3;
		ray_num += 1;
	}
}

/* the function that starts everything rendering wise */
int	render(t_data *data, char map[MAP_HEIGHT][MAP_WIDTH])
{
	if (find_player_grid(data, map))
	{
		write(2, "Issue!\n", 7);
		return (1);
	}
	draw_ceiling_and_floor(data);
	ray_caster(data, map);
	return (0);
}
