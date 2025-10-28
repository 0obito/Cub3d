#include "./header.h"

void	colorize_grid(int grid_x, int grid_y, t_imgdata *img, unsigned int color)
{
	char	*dst;
	int		px;
	int		py;

	py = grid_y * GRID_HEIGHT;
	while (py < (grid_y + 1) * GRID_HEIGHT)
	{
		px = grid_x * GRID_WIDTH;
		while (px < (grid_x + 1) * GRID_WIDTH)
		{
			dst = img->img_add + py * img->line_length + px * (img->bits_per_pixel / 8);
			*(unsigned int *)dst = color;
			px++;
		}
		py++;
	}
	return ;
}

void	draw_player(int grid_x, int grid_y, t_imgdata *img, unsigned int color)
{
	char	*dst;
	int		px;
	int		py;
	int		counter_x;
	int		counter_y;

	py = (grid_y * GRID_HEIGHT) + (GRID_HEIGHT / 2) - 2;
	counter_y = 0;
	while (counter_y < 5)
	{
		px = (grid_x * GRID_WIDTH) + (GRID_WIDTH / 2) - 2;
		counter_x = 0;
		while (counter_x < 5)
		{
			dst = img->img_add + py * img->line_length + px * (img->bits_per_pixel / 8);
			*(unsigned int *)dst = color;
			px++;
			counter_x++;
		}
		py++;
		counter_y++;
	}
	return ;
}

int	initiate_mlx(t_mlx *mlx, t_imgdata *img)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (write(1, "Issue Creating Connection!\n", 27), 1);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "lo3ba.exe");
	if (!mlx->win_ptr)
		return (write(1, "Issue Creating Window!\n", 23), 1);
	img->img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!img->img_ptr)
		return (write(1, "Issue Creating Image!\n", 22), 1);
	img->img_add = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel, &img->line_length, &img->endian);
	if (!img->img_add)
		return (write(1, "Issue Retrieving Address!\n", 26), 1);
	return (0);
}

// static char	mip[][] =
// {
// 	{2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
// 	{2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
// 	{1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 2, 2, 2, 2},
// 	{1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 2, 2, 2, 2},
// 	{1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 2, 2, 2, 2},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 2, 2, 2, 2},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 2, 2, 2, 2},
// 	{1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 'N', 0, 1, 1, 1, 2},
// 	{1, 1, 1, 1, 0, 1, 1, 1, 2, 1, 1, 1, 0, 1, 0, 1, 2, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 2, 2, 2, 2},
// 	{1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2}
// };

static char	map[MAP_HEIGHT][MAP_WIDTH] =
{
	{1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 0, 'P', 0, 1, 1},
	{1, 1, 1, 1, 0, 0, 0, 1},
	{1, 1, 1, 0, 0, 0, 0, 1},
	{1, 1, 0, 0, 0, 1, 0, 1},
	{1, 1, 1, 0, 0, 1, 1, 1},
	{1, 1, 1, 0, 0, 1, 0, 1},
	{1, 1, 1, 0, 0, 0, 0, 1},
	{1, 1, 0, 0, 1, 0, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1}
};

int	main()
{
	t_mlx		mlx;
	t_imgdata	img;
	// char		**grid;
	int			x;
	int			y;

	if (initiate_mlx(&mlx, &img))
		return (1);
	y = 0;
	while (y < MAP_HEIGHT)
	{
		x = 0;
		while (x < MAP_WIDTH)
		{
			if (map[y][x] == 1)
				colorize_grid(x, y, &img, 0x00808080);
			else
			{
				colorize_grid(x, y, &img, 0x00A0D9EF);
				if (map[y][x] == 'P')
				{
					draw_player(x, y, &img, 0x001434A4);
				}
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, img.img_ptr, 0, 0);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
