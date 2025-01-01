

#include "../includes/fdf.h"

int main(int ac, char *av[])
{
	t_fdf *fdf;

	if (!fdf_init(ac, av, &fdf))
		return(EXIT_FAILURE);
	if(!fdf)
	if (!fdf_draw(fdf))
		return (EXIT_FAILURE);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img->img_ptr, 0, 0);
	set_hooks(fdf);
	mlx_loop(fdf->mlx_ptr);
	return (0);
}