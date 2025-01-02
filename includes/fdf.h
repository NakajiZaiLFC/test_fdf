#ifndef FDF_H
# define FDF_H

# define ESC 65307
# define ISO_ANGLE_X 0.523599
# define ISO_ANGLE_Y 0.523599
# define SCALE 20

# include "../ft_printf/include/ft_printf.h"
# include "../minilibx/mlx.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
}			t_img;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		color;
}			t_point;

typedef struct s_map
{
	int		width;
	int		height;
	t_point	**points;
}			t_map;

typedef struct s_fdf
{
	int		win_width;
	int		win_height;
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	t_map	map;
}			t_fdf;

bool		fdf_init(int ac, char *av[], t_fdf *fdf);
int			close_window(t_fdf *fdf);
bool		fdf_draw(t_fdf *fdf);
bool		set_hooks(t_fdf *fdf);
void		free_split(char **split);
int			ft_atoi_base(char *str, int base);
int			ft_strlncmp(char *s1, char *s2, int n);
bool		make_mlx_window(t_fdf *fdf);
t_point		iso_projection(int x, int y, int z);
void		fdf_free(t_fdf *fdf);
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
void		draw_line_to_image(t_img *img, t_point p0, t_point p1, int color);

#endif