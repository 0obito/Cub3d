#include "./header.h"

int	main()
{
	t_mlx		mlx;
	t_imgdata	img;
	char		*dst;
	int			x;
	int			y;

	mlx.mlx_ptr = mlx_init();
	if (!mlx.mlx_ptr)
		return (write(1, "Issue Creating Connection!\n", 27), 2);
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, 800, 800, "Bunda");
	if (!mlx.win_ptr)
		return (write(1, "Issue Creating Window!\n", 23), 2);
	img.img_ptr = mlx_new_image(mlx.mlx_ptr, 800, 800);
	if (!img.img_ptr)
		return (write(1, "Issue Creating Image!\n", 22), 2);
	img.img_add = mlx_get_data_addr(img.img_ptr, &img.bits_per_pixel, &img.line_length, &img.endian);
	if (!img.img_add)
		return (write(1, "Issue Retrieving Address!\n", 26), 2);
	y = 0;
	while (y < 800)
	{
		x = 0;
		while (x < 800)
		{
			dst = img.img_add + (y * img.line_length + x * (img.bits_per_pixel / 8));
			(unsigned char)(*dst) = 255;
			// mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, x, y, 0xFFFFFFFF);
			x++;
		}
		y++;
	}
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
