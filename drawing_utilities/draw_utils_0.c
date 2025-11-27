/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:51:32 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/11/27 11:48:37 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* a function that colors the ceiling and the floor inside the window */
void	draw_ceiling_and_floor(t_data *data)
{
	char			*dst;
	unsigned int	color;
	int				y;
	int				x;

	color = 0xFF663300;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		(void)((y == (WIN_HEIGHT / 2)) && (color = 0xFF1B1C1D));
		x = 0;
		while (x < WIN_WIDTH)
		{
			dst = data->img->img_add + (y * data->img->line_length)
				+ (x * (data->img->bpp / 8));
			*(unsigned int *)dst = color;
			x += 1;
		}
		y += 1;
	}
	return ;
}

/* a function that draws a vertical line representing a casted ray*/
void	draw_wall(t_data *data, int ray_num, double corr_angle)
{
	char	*dst;
	int		counter;
	double	wall_height;
	t_coord	params;

	data->ray->ray_length *= cos(corr_angle * (M_PI / 180));
	wall_height = WIN_HEIGHT * (100 / (data->ray->ray_length
				* cos(corr_angle * (M_PI / 180))));
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
	return ;
}
