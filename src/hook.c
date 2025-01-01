

#include "../includes/fdf.h"

static int _key_press(int key, t_fdf *fdf);
static int _close_window(t_fdf *fdf);

bool set_hooks(t_fdf *fdf)
{
	mlx_key_hook(fdf->win_ptr, 2, 1L<<0, _key_press, fdf);
	mlx_hook(fdf->win_ptr, 17, 1L<<0, _close_window, fdf);
	return (true);
}

static int _key_press(int key, t_fdf *fdf)
{
	if (key == ESC)
		_close_window(fdf);
	return (0);
}

static int _close_window(t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx_ptr, fdf->img->img_ptr);
	mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	mlx_destroy_display(fdf->mlx_ptr);
	fdf_free(fdf);
	exit(EXIT_SUCCESS);
}

