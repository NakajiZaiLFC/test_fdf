/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakajim <snakajim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 15:48:28 by snakajim          #+#    #+#             */
/*   Updated: 2025/01/01 15:48:29 by snakajim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	fdf_free(t_fdf *fdf)
{
	int i;

	i = 0;
	if (fdf->map.points)
	{
		while (fdf->map.points[i])
			free(fdf->map.points[i++]);
		free(fdf->map.points);
	}
}