/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakajim <snakajim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 15:48:35 by snakajim          #+#    #+#             */
/*   Updated: 2025/01/02 13:11:07 by snakajim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int	_key_press(int key, t_fdf *fdf);

bool	set_hooks(t_fdf *fdf)
{
	mlx_key_hook(fdf->win_ptr, _key_press, fdf);
	mlx_hook(fdf->win_ptr, 17, 1L << 0, close_window, fdf);
	return (true);
}

static int	_key_press(int key, t_fdf *fdf)
{
	if (key == ESC)
		close_window(fdf);
	return (0);
}

int	close_window(t_fdf *fdf)
{
	if (!fdf)
		return (0);
	if (fdf->img.img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->img.img_ptr);
	if (fdf->win_ptr)
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	if (fdf->mlx_ptr)
	{
		mlx_destroy_display(fdf->mlx_ptr);
	}
	fdf_free(fdf);
	exit(EXIT_SUCCESS);
}
