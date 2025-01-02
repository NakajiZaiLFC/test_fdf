/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakajim <snakajim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 15:37:58 by snakajim          #+#    #+#             */
/*   Updated: 2025/01/02 14:22:09 by snakajim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_point	iso_projection(int x, int y, int z, t_fdf *fdf)
{
	t_point	p;
	double	scale;

	// マップサイズに基づいて自動スケーリング
	scale = fmin((fdf->win_width / (fdf->map.width * 2.0)), (fdf->win_height
				/ (fdf->map.height * 2.0)));
	// 座標変換
	x = (x - fdf->map.width / 2.0) * scale;
	y = (y - fdf->map.height / 2.0) * scale;
	z = z * (scale * 0.3); // z軸は通常の半分のスケール
	// 等角投影の計算
	p.x = (x - y) * cos(ISO_ANGLE_X);
	p.y = (x + y) * sin(ISO_ANGLE_Y) - z;
	// ウィンドウの中心に配置
	p.x += fdf->win_width / 2;
	p.y += fdf->win_height / 2;
	return (p);
}

bool	fdf_draw(t_fdf *fdf)
{
	int		x;
	int		y;
	t_point	p0;
	t_point	p1;

	if (!fdf->mlx_ptr || !fdf->win_ptr)
		return (false);
	if (fdf->img.img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->img.img_ptr);
	fdf->img.img_ptr = mlx_new_image(fdf->mlx_ptr, fdf->win_width,
			fdf->win_height);
	if (!fdf->img.img_ptr)
		return (false);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img_ptr, &fdf->img.bpp,
			&fdf->img.size_line, &fdf->img.endian);
	if (!fdf->img.addr)
		return (false);
	memset(fdf->img.addr, 0, fdf->img.size_line * fdf->win_height);
	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			p0 = iso_projection(x, y, fdf->map.points[y][x].z, fdf);
			if (x < fdf->map.width - 1)
			{
				p1 = iso_projection(x + 1, y, fdf->map.points[y][x + 1].z, fdf);
				draw_line_to_image(&fdf->img, p0, p1,
					fdf->map.points[y][x].color);
			}
			if (y < fdf->map.height - 1)
			{
				p1 = iso_projection(x, y + 1, fdf->map.points[y + 1][x].z, fdf);
				draw_line_to_image(&fdf->img, p0, p1,
					fdf->map.points[y][x].color);
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img.img_ptr, 0, 0);
	return (true);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < 1920 && y >= 0 && y < 1080)
	{
		dst = img->addr + (y * img->size_line + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_line_to_image(t_img *img, t_point p0, t_point p1, int color)
{
	int dx;
	int dy;
	int sx;
	int sy;
	int err;
	int e2;
	t_point current;

	dx = abs(p1.x - p0.x);
	dy = abs(p1.y - p0.y);
	sx = p0.x < p1.x ? 1 : -1;
	sy = p0.y < p1.y ? 1 : -1;
	err = (dx > dy ? dx : -dy) / 2;
	current = p0;

	while (1)
	{
		my_mlx_pixel_put(img, current.x, current.y, color);
		if (current.x == p1.x && current.y == p1.y)
			break ;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			current.x += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			current.y += sy;
		}
	}
}