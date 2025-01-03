/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakajim <snakajim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:44:47 by snakajim          #+#    #+#             */
/*   Updated: 2025/01/03 17:13:16 by snakajim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x <= WIN_WIDTH && y >= 0 && y <= WIN_HEIGHT)
	{
		dst = img->addr + (y * img->size_line + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	fdf_draw(t_fdf *fdf, int x, int y)
{
	t_point	p0;
	t_point	p1;

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
}
