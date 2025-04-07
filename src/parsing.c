/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:13:41 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/03 16:23:55 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdlib.h>

t_point	create_point(double x, double y, double z)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = z;
	point.px = x;
	point.py = y;
	point.pz = z;
	return (point);
}

/*t_point	project_point(t_point point)*/
/*{*/
/*	t_point	p_point;*/
/**/
/*	p_point.x = point.x * cos(ANGLE) + point.y * cos(ANGLE + 2) + point.z * cos(ANGLE - 2) + WIDTH / 2;*/
/*	p_point.y = point.x * sin(ANGLE) + point.y * sin(ANGLE + 2) + point.z * sin(ANGLE - 2) + HEIGHT / 2;*/
/*	p_point.z = point.z;*/
/*	return (p_point);*/
/*}*/

int	open_map(char map_filename[])
{
	int	map_fd;

	map_fd = open(map_filename, O_RDONLY);
	if (map_fd < 0)
	{
		perror(map_filename);
		exit(EXIT_FAILURE);
	}
	return (map_fd);
}

void	read_map(t_map *map, int map_fd)
{
	char	*line;
	size_t	col;
	size_t	row;

	row = 0;
	line = get_next_line(map_fd);
	if (!line)
		invalid_map(map);
	init_map(map, map_fd, count_words(line, ' '));
	while (line)
	{
		if (count_words(line, ' ') != map->len)
			invalid_map(map);
		if ((row + 1) > map->h_capacity)
			double_array_size(map);
		map->height = row + 1;
		col = 0;
		while (col < map->len)
		{
			map->map[row][col] = create_point(col, row, get_value(line, col));
			++col;
		}
		free(line);
		++row;
		line = get_next_line(map_fd);
	}
}

size_t	count_words(char *s, char sep)
{
	size_t	size;
	int		i;
	int		is_first_char;

	is_first_char = 1;
	i = 0;
	size = 0;
	while (s[i])
	{
		if (s[i] == sep)
			is_first_char = 1;
		else if (is_first_char)
		{
			++size;
			is_first_char = 0;
		}
		++i;
	}
	return (size);
}

int	ft_strlen_ws(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != ' ' && str[i] != '\n')
		++i;
	return (i);
}

int	get_value(char *line, int x)
{
	int		word_index;
	int		i;
	int		map_len;
	int		n;

	map_len = ft_strlen(line);
	i = 0;
	word_index = 0;
	while (word_index < x && i < map_len)
	{
		if (line[i] == ' ')
			++word_index;
		++i;
	}
	n = ft_atoi(line + i);
	return (n);
}

void	print_arr(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map && map[i])
	{
		ft_printf("%s\n", map[i]);
		++i;
	}
}
