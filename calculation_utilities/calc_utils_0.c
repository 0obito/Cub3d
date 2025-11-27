/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_utils_0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:23:52 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/11/27 11:35:03 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	block_to_pixel_coords(t_data *data, int j, int i)
{
	data->player->grid_y = j;
	data->player->grid_x = i;
	data->player->y = (j + 1 / (double)2) * (WIN_HEIGHT / (double)MAP_HEIGHT);
	data->player->x = (i + 1 / (double)2) * (WIN_WIDTH / MAP_WIDTH);
	if (data->player->direction == 'N')
		data->player->starting_angle = M_PI / 2;
	else if (data->player->direction == 'S')
		data->player->starting_angle = M_PI * 3 / 2;
	else if (data->player->direction == 'E')
		data->player->starting_angle = 0;
	else if (data->player->direction == 'W')
		data->player->starting_angle = M_PI;
}

void	direction_corrector(t_data *data, double angle)
{
	(void)((angle >= 0) && (angle < (M_PI / 2))
		&& (data->ray->y_dir = -1) && (data->ray->x_dir = 1));
	(void)((angle >= (M_PI / 2)) && (angle < M_PI)
		&& (data->ray->y_dir = -1) && (data->ray->x_dir = -1));
	(void)((angle >= M_PI) && (angle < (M_PI * 3 / 2 ))
		&& (data->ray->y_dir = 1) && (data->ray->x_dir = -1));
	(void)((angle >= (M_PI * 3 / 2 )) && (angle < (M_PI * 2))
		&& (data->ray->y_dir = 1) && (data->ray->x_dir = 1));
}

double	deg_to_rad(double angle)
{
	double	ang;

	ang = angle;
	if (ang < 0)
		while (ang < 0)
			ang += 360;
	if (ang > 360)
		ang = fmod(ang, 360);
	ang *= (M_PI / 180);
	return (ang);
}

double	rad_to_deg(double angle)
{
	double	ang;

	ang = angle;
	ang *= (180 / M_PI);
	if (ang < 0)
		while (ang < 0)
			ang += 360;
	if (ang > 360)
		ang = fmod(ang, 360);
	return (ang);
}
