/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakajim <snakajim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:19:31 by snakajim          #+#    #+#             */
/*   Updated: 2025/01/03 17:16:03 by snakajim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define ESC 65307
# define ISO_ANGLE_X 0.523599
# define ISO_ANGLE_Y 0.523599
# define M_PI 3.141592
# define SCALE 20
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

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

typedef struct s_plane
{
	int		x;
	int		y;
}			t_plane;

typedef struct s_iso_param
{
	double	scale;
	double	angle_x;
	double	angle_y;
	double	projected_x;
	double	projected_y;
	double	projected_z;
}			t_iso_param;

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

typedef struct s_line_data
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		error;
	int		error2;
	t_point	current;
}			t_line_data;

typedef struct s_fdf
{
	int		win_width;
	int		win_height;
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	t_map	map;
}			t_fdf;

void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
t_point		iso_projection(int x, int y, int z, t_fdf *fdf);
void		init_line_data(t_line_data *line, t_point p0, t_point p1);
void		update_line_position(t_line_data *line);
bool		fdf_init(int ac, char *av[], t_fdf *fdf);
int			close_window(t_fdf *fdf);
void		fdf_draw(t_fdf *fdf, int x, int y);
bool		set_hooks(t_fdf *fdf);
bool		set_points_info(char *file_name, t_map *map);
void		free_split(char **split);
int			ft_atoi_base(char *str, int base);
int			ft_strlncmp(char *s1, char *s2, int n);
bool		make_mlx_window(t_fdf *fdf);
t_point		iso_projection(int x, int y, int z, t_fdf *fdf);
void		fdf_free(t_fdf *fdf);
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
void		draw_line_to_image(t_img *img, t_point p0, t_point p1, int color);
void		mlx_free(t_fdf *fdf);
void		draw_line_to_image(t_img *img, t_point p0, t_point p1, int color);
void		err_fdf_free(t_fdf *fdf);
#endif