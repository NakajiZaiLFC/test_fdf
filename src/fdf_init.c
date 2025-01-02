/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakajim <snakajim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 15:48:23 by snakajim          #+#    #+#             */
/*   Updated: 2025/01/02 20:20:11 by snakajim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static bool	_create_map(char *file_name, t_fdf *fdf);
static bool	_get_map_size(char *file_name, int *width, int *height);

bool	fdf_init(int ac, char *av[], t_fdf *fdf)
{
	if (ac != 2)
		return (ft_printf("Error: invalid number of arguments\n"), false);
	if (ft_strlncmp(av[1], ".fdf", 4) != 0)
		return (ft_printf("Error: invalid file name\n"), false);
	if (open(av[1], O_RDONLY) < 0)
		return (ft_printf("Error: can't read fdf file\n"), false);
	if (!_create_map(av[1], fdf))
		return (ft_printf("Error: can't mapping\n"), false);
	return (true);
}

static bool	_create_map(char *file_name, t_fdf *fdf)
{
	int	i;

	i = 0;
	if (!_get_map_size(file_name, &fdf->map.width, &fdf->map.height))
		return (false);
	printf("test\n");
	fdf->map.points = (t_point **)malloc(sizeof(t_point *) * fdf->map.height
			+ 1);
	if (!fdf->map.points)
		return (false);
	while (i < fdf->map.height)
	{
		fdf->map.points[i] = (t_point *)malloc(sizeof(t_point)
				* fdf->map.width);
		if (!fdf->map.points[i])
			return (err_fdf_free(fdf), false);
		i++;
	}
	if (!set_points_info(file_name, &fdf->map))
		return (err_fdf_free(fdf), false);
	return (true);
}

static int	_count_width(char *line)
{
	char	**split_line;
	int		width;

	width = 0;
	split_line = ft_split(line, ' ');
	if (!split_line)
		return (0);
	while (split_line[width] != NULL)
		width++;
	free_split(split_line);
	return (width);
}

static bool	_get_map_size(char *file_name, int *width, int *height)
{
	char	*line;
	int		fd;

	*width = 0;
	*height = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (false);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (*width == 0)
			*width = _count_width(line);
		else if (*width != _count_width(line))
		{
			free(line);
			close(fd);
			return (false);
		}
		(*height)++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (true);
}
