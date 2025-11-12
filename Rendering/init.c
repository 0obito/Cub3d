/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:48:34 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/11/04 16:48:35 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* a func that sets up some necessary data at the beginning of the program */
int	initiate_mlx(t_data *data, t_mlxdata *mlx, t_imgdata *img)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (write(1, "Issue Creating Connection!\n", 27), 1);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Cub0d");
	if (!mlx->win_ptr)
		return (write(1, "Issue Creating Window!\n", 23), 1);
	img->img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!img->img_ptr)
		return (write(1, "Issue Creating Image!\n", 22), 1);
	img->img_add = mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->line_length, &img->endian);
	if (!img->img_add)
		return (write(1, "Issue Retrieving Address!\n", 26), 1);
	data->mlx = mlx;
	data->img = img;
	return (0);
}

int	initiate_player_and_ray(t_data *data, t_playerdata *player, t_ray *ray)
{
	player->y = -1;
	player->x = -1;
	ray->nearest_blocky = 0;
	ray->nearest_blockx = 0;
	data->player = player;
	data->ray = ray;
	return (0);
}
