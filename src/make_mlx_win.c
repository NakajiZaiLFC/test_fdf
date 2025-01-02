/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_mlx_win.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakajim <snakajim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 15:48:50 by snakajim          #+#    #+#             */
/*   Updated: 2025/01/01 20:34:45 by snakajim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

bool	make_mlx_window(t_fdf *fdf)
{
	void	*mlx;
	void	*win;
	void	*img;

	fdf->win_width = 1920;
	fdf->win_height = 1080;
	mlx = mlx_init();
	if (!mlx)
		return (false);
	fdf->mlx_ptr = mlx;
	win = mlx_new_window(mlx, fdf->win_width, fdf->win_height, "FDF Test");
	if (!win)
		return (false);
	fdf->win_ptr = win;
	img = mlx_new_image(mlx, fdf->win_width, fdf->win_height);
	if (!img)
		return (false);
	fdf->img.img_ptr = img;
	fdf->img.addr = mlx_get_data_addr(fdf->img.img_ptr, &fdf->img.bpp,
			&fdf->img.size_line, &fdf->img.endian);
	if (!fdf->img.addr)
		return (false);
	return (true);
}

// bool	make_mlx_window(t_fdf *fdf)
// {
// 	fdf->win_width = 1920;
// 	fdf->win_height = 1080;
// 	if (!(fdf->mlx_ptr = mlx_init()))
// 		return (false);
// 	if (!(fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, fdf->win_width,
// 				fdf->win_height, "FDF")))
// 		return (false);
// 	if (!(fdf->img.img_ptr = mlx_new_image(fdf->mlx_ptr, fdf->win_width,
// 				fdf->win_height)))
// 		return (false);
// 	if (!(fdf->img.addr = mlx_get_data_addr(fdf->img.img_ptr, &fdf->img.bpp,
// 				&fdf->img.size_line, &fdf->img.endian)))
// 		return (false);
// 	return (true);
// }