/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakajim <snakajim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:44:47 by snakajim          #+#    #+#             */
/*   Updated: 2025/01/02 19:40:30 by snakajim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_point	iso_projection(int x, int y, int z, t_fdf *fdf)
{
	t_point	p;
	double	scale;
	double	projected_x;
	double	projected_y;

	double angle_x = M_PI / 6; // 30度
	double angle_y = M_PI / 6; // 30度
	// より適切なスケール計算
	scale = fmin((fdf->win_width / (fdf->map.width * sqrt(2))), (fdf->win_height
				/ (fdf->map.height * sqrt(2)))) * 0.7;
	// 座標変換（より正確な変換）
	projected_x = (x - fdf->map.width / 2.0) * scale;
	projected_y = (y - fdf->map.height / 2.0) * scale;
	double projected_z = z * (scale * 0.5); // z軸のスケールを調整
	// 等角投影の計算
	p.x = (projected_x - projected_y) * cos(angle_x);
	p.y = ((projected_x + projected_y) * sin(angle_y) - projected_z);
	// 画面中央に配置
	p.x += fdf->win_width / 2;
	p.y += fdf->win_height / 2;
	return (p);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x <= WIN_WIDTH && y >= 0 && y <= WIN_HEIGHT)
	{
		dst = img->addr + (y * img->size_line + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
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

void	draw_line_to_image(t_img *img, t_point p0, t_point p1, int color)
{
	t_line_data line;

	line.dx = abs(p1.x - p0.x);
	line.dy = abs(p1.y - p0.y);
	line.sx = p0.x < p1.x ? 1 : -1;
	line.sy = p0.y < p1.y ? 1 : -1;
	line.error = (line.dx > line.dy ? line.dx : -line.dy) / 2;
	line.current = p0;

	while (1)
	{
		if (line.current.x >= 0 && line.current.x < WIN_WIDTH
			&& line.current.y >= 0 && line.current.y < WIN_HEIGHT)
			my_mlx_pixel_put(img, line.current.x, line.current.y, color);
		if (line.current.x == p1.x && line.current.y == p1.y)
			break ;
		line.error2 = line.error;
		if (line.error2 > -line.dx)
		{
			line.error -= line.dy;
			line.current.x += line.sx;
		}
		if (line.error2 < line.dy)
		{
			line.error += line.dx;
			line.current.y += line.sy;
		}
	}
}