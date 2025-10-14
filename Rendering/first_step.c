#include "./header.h"

int	main()
{
	t_mlx		mlx;
	t_imgdata	img;

	mlx.mlx_ptr = mlx_init();
	if (!mlx.mlx_ptr)
		return (write(1, "Issue Creating Connection!\n", 27), 2);
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, 500, 500, "Bunda");
	if (!mlx.win_ptr)
		return (write(1, "Issue Creating Window!\n", 23), 2);
	img.img_ptr = mlx_new_image(mlx.mlx_ptr, 500, 500);
	if (!img.img_ptr)
		return (write(1, "Issue Creating Image!\n", 22), 2);
	img.img_add = mlx_get_data_addr(img.img_ptr, &img.bits_per_pixel, &img.line_length, &img.endian);
	if (!img.img_add)
		return (write(1, "Issue Retrieving Address!\n", 26), 2);
	mlx_string_put(mlx.mlx_ptr, mlx.win_ptr, 250, 250, 0xFFFFFF, "Well hello there.\n\n\n\n\n\nThis is interesting!");
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
