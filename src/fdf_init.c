/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakajim <snakajim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 15:48:23 by snakajim          #+#    #+#             */
/*   Updated: 2025/01/02 13:46:07 by snakajim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static bool	_create_map(char *file_name, t_fdf *fdf);
static bool	_get_map_size(char *file_name, int *width, int *height);
static bool	_set_points_info(char *file_name, t_map *map);
static int	_get_color(char *str);

bool	fdf_init(int ac, char *av[], t_fdf *fdf)
{
	if (ac != 2)
		return (ft_printf("Error: invalid number of arguments\n"), false);
	if (ft_strlncmp(av[1], ".fdf", 4) != 0)
		return (ft_printf("Error: invalid file name\n"), false);
	if (!_create_map(av[1], fdf)) // ok
		return (fdf_free(fdf), false);
	if (!make_mlx_window(fdf))
		return (fdf_free(fdf), false);
	return (true);
}

static bool	_create_map(char *file_name, t_fdf *fdf)
{
	int	i;

	i = 0;
	if (!_get_map_size(file_name, &fdf->map.width, &fdf->map.height))
		return (false);
	fdf->map.points = (t_point **)malloc(sizeof(t_point *) * fdf->map.height
			+ 1);
	if (!fdf->map.points)
		return (false);
	while (i < fdf->map.height)
	{
		fdf->map.points[i] = (t_point *)malloc(sizeof(t_point)
				* fdf->map.width);
		if (!fdf->map.points[i])
		{
			while (i >= 0)
				free(fdf->map.points[i--]);
			free(fdf->map.points);
			return (false);
		}
		i++;
	}
	if (!_set_points_info(file_name, &fdf->map))
		return (false);
	for (int i = 0; i < fdf->map.height; i++)
	{
		for (int j = 0; j < fdf->map.width; j++)
		{
			printf("points[%d][%d].x: %d\n", i, j, fdf->map.points[i][j].x);
			printf("points[%d][%d].y: %d\n", i, j, fdf->map.points[i][j].y);
			printf("points[%d][%d].z: %d\n", i, j, fdf->map.points[i][j].z);
			printf("points[%d][%d].color: %d\n", i, j,
				fdf->map.points[i][j].color);
		}
	}
	return (true);
}

static bool	_get_map_size(char *file_name, int *width, int *height)
{
	char	*line;
	char	**split_line;
	int		fd;

	*width = 0;
	*height = 0;
	line = NULL;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (false);
	while ((line = get_next_line(fd)))
	{
		if (*width == 0)
		{
			split_line = ft_split(line, ' ');
			while (split_line[*width])
				(*width)++;
			free_split(split_line);
		}
		(*height)++;
		free(line);
	}
	close(fd);
	return (true);
}

static bool	_set_points_info(char *file_name, t_map *map)
{
	int		i;
	int		j;
	char	*line;
	char	**split;
	int		z_value;
	int		color_value;
	int		fd;

	i = 0;
	line = NULL;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (false);
	while (((line = get_next_line(fd)) && i < map->height))
	{
		split = ft_split(line, ' ');
		if (!split)
			return (false);
		for (int k = 0; split[k]; k++)
			j = 0;
		while (split[j] && j < map->width)
		{
			z_value = ft_atoi(split[j]);
			color_value = _get_color(split[j]);
			map->points[i][j].x = j;
			map->points[i][j].y = i;
			map->points[i][j].z = z_value;
			map->points[i][j].color = color_value;
			j++;
		}
		free_split(split);
		free(line);
		i++;
	}
	close(fd);
	return (true);
}

static int	_get_color(char *str)
{
	char	*color_str;
	int		color;

	color = 0xFFFFFF;
	color_str = ft_strchr(str, ',');
	if (color_str)
	{
		color_str++;
		if (color_str[0] == '0' && (color_str[1] == 'x' || color_str[1] == 'X'))
			color = ft_atoi_base(color_str + 2, 16);
	}
	return (color);
}
