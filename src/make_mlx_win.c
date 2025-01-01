

#include "../includes/fdf.h"

bool make_mlx_window(t_fdf *fdf)
{
	fdf->win_width = 1920;
	fdf->win_height = 1080;
	if (!(fdf->mlx_ptr = mlx_init()))
		return (false);
	if (!(fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, fdf->win_width, fdf->win_height, "FDF")))
		return (false);
	if (!(fdf->img->img_ptr = mlx_new_image(fdf->mlx_ptr, fdf->win_width, fdf->win_height)))
		return (false);
	if (!(fdf->img->addr = mlx_get_data_addr(fdf->img->img_ptr, &fdf->img->bpp, &fdf->img->size_line, &fdf->img->endian)))
		return (false);
	return (true);
}