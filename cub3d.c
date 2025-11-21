/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:37:52 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/11/05 15:37:54 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

int	main()
{
	t_data			data;
	t_mlxdata		mlx;
	t_imgdata		img;
	t_playerdata	player;
	t_ray			ray;

	char			map[MAP_HEIGHT][MAP_WIDTH] =
	{
		"1111111111",
		"1100000001",
		"1111000001",
		"11110S0001",
		"1111001001",
		"1111101001",
		"1000011111",
		"1111111111",
		"1111111111",
		"1111111111",
	};

	// /* init the connection and open the window */
	if (initiate_mlx(&data, &mlx, &img)
		|| initiate_player_and_ray(&data, &player, &ray))
		return (1);
	/* draw on the image */
	render(&data, map);

	/* put the image to the window */
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, img.img_ptr, 0, 0);

	/* liten on keys and do stuff */
	/*
	mlx_key_hook(mlx.win_ptr, key_hook, &vars);
	*/

	/* keep the loop running and the window showing */
	mlx_loop(mlx.mlx_ptr);

	return (0);
}
