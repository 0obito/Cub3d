/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelmsafe <aelmsafe@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:37:14 by aelmsafe          #+#    #+#             */
/*   Updated: 2025/11/27 14:37:16 by aelmsafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// !!! might not need this if I can figure it from the parsing part !!!
/* a function that finds the player position in the map */
int	find_player_grid(t_data *data, char map[MAP_HEIGHT][MAP_WIDTH])
{
	int		j;
	int		i;

	j = 0;
	// here, 10 is the number of lines in the map,
	// will have to change it later to a `non hardcoded value`.
	while (j < 10)
	{
		i = 0;
		// and here, 10 is the number of blocks in the current line,
		// will have to change it later as well to a `non hardcoded value`.
		while (i < 10)
		{
			if ((map[j][i] == 'N') || (map[j][i] == 'S')
				|| (map[j][i] == 'E') || (map[j][i] == 'W'))
			{
				data->player->direction = map[j][i];
				block_to_pixel_coords(data, j, i);
				return (0);
			}
			i += 1;
		}
		j += 1;
	}
	return (1);
}
