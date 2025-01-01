

#include "../includes/fdf.h"

static bool _create_map(char *file_name, t_fdf *fdf);
static void _get_map_size(int file_name, int *width, int *height);
static bool _set_points_info(int fd, t_map *map);
static int _get_color(char *str);

bool fdf_init(int ac, char *av[], t_fdf *fdf)
{
	if (ac != 2)
		return (ft_putstr("Error: invalid number of arguments\n"), false);
	if (ft_strlncmp(av[1], ".fdf", 4) != 0)
		return (ft_putstr("Error: invalid file name\n"), false);
	if (!_create_map(av[1], fdf))
		return (fdf_free(fdf), false);
	if (!make_mlx_window(fdf))
		return (fdf_free(fdf), false);
	return (true);
}

static bool _create_map(char *file_name, t_fdf *fdf)
{
	int fd;
	char *line;
	char **fdf_str;

	if ((fd = open(file_name, O_RDONLY)) < 0)
		return (false);
	_get_map_size(fd, &fdf->map.width, &fdf->map.height);
	fdf->map.points = (t_point **)malloc(sizeof(t_point *) * fdf->map.height);
	if (!fdf->map.points)
		return (false);
	if (!_set_points_info(fd, &fdf->map))
		return (false);
	return (true);
}

static void _get_map_size(int fd, int *width, int *height)
{
	int fd;
	char *line;
	char **split_line;

	// *height = 0;
	// *width = 0; TODO
	while (get_next_line(fd))
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

static bool _set_points_info(int fd, t_map *map)
{
	int i;
	int j;
	char *line;
	char **split;

	while (line = get_next_line(fd))
	{
		i = 0;
		map->points[i] = (t_point *)malloc(sizeof(t_point) * map->width);
		split = ft_split(line, ' ');
		if (!map->points[i] || !split)
			return (false);
		j = 0;
		while (split[j] && j < map->width)
		{
			map->points[i][j].z = ft_atoi(split[j]);
			map->points[i][j].color = _get_color(split[j]);
			j++;
		}
		free_split(split);
		free(line);
		i++;
	}
	close(fd);
}

static int _get_color(char *str)
{
	char *color_str;
	int color;

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
