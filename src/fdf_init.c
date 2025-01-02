/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakajim <snakajim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 15:48:23 by snakajim          #+#    #+#             */
/*   Updated: 2025/01/01 20:52:05 by snakajim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static bool	_create_map(char *file_name, t_fdf *fdf);
static void	_get_map_size(int fd, int *width, int *height);
static bool	_set_points_info(int fd, t_map *map);
static int	_get_color(char *str);

bool	fdf_init(int ac, char *av[], t_fdf *fdf)
{
	if (ac != 2)
		return (ft_printf("Error: invalid number of arguments\n"), false);
	if (ft_strlncmp(av[1], ".fdf", 4) != 0)
		return (ft_printf("Error: invalid file name\n"), false); // ok
	if (!_create_map(av[1], fdf))
		return (fdf_free(fdf), false);
	if (!make_mlx_window(fdf))
		return (fdf_free(fdf), false);
	return (true);
}

static bool	_create_map(char *file_name, t_fdf *fdf)
{
	int	fd;
	int	i;

	i = 0;
	if ((fd = open(file_name, O_RDONLY)) < 0)
		return (false);
	_get_map_size(fd, &fdf->map.width, &fdf->map.height);
	fdf->map.points = (t_point **)malloc(sizeof(t_point *) * fdf->map.height);
	if (!fdf->map.points)
		return (false);
	while (i < fdf->map.height)
	{
		fdf->map.points[i] = (t_point *)malloc(sizeof(t_point)
				* fdf->map.width);
		if (!fdf->map.points[i])
			return (false);
		i++;
	}
	if (!_set_points_info(fd, &(fdf->map)))
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

static void	_get_map_size(int fd, int *width, int *height)
{
	char	*line;
	char	**split_line;

	*width = 0;
	*height = 0;
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
}

static bool	_set_points_info(int fd, t_map *map)
{
	int		i;
	int		j;
	char	*line;
	char	**split;
	int		z_value;
	int		color_value;

	i = 0;
	while ((line = get_next_line(fd)) && i < map->height)
	{
		printf("test\n");
		printf("Debug: Line %d: %s\n", i, line); // 読み込んだ行の内容を確認
		split = ft_split(line, ' ');
		if (!split)
			return (false);
		printf("Debug: Split contents for line %d:\n", i);
		for (int k = 0; split[k]; k++)
		{
			printf("split[%d]: %s\n", k, split[k]); // 分割後の文字列を確認
		}
		j = 0;
		while (split[j] && j < map->width)
		{
			z_value = ft_atoi(split[j]);
			color_value = _get_color(split[j]);
			printf("Debug: Position [%d][%d] - Converting %s to z=%d, \
				color=%d\n",
					i,
					j,
					split[j],
					z_value,
					color_value); // 変換値を確認
			map->points[i][j].x = j;
			map->points[i][j].y = i;
			map->points[i][j].z = z_value;
			map->points[i][j].color = color_value;
			printf("Debug: After setting - point[%d][%d]: x=%d, y=%d, z=%d, \
					color = %d\n ",
					i,
					j,
					map->points[i][j].x,
					map->points[i][j].y,
					map->points[i][j].z,
					map->points[i][j].color); // 設定後の値を確認
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
