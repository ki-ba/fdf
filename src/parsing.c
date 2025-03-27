/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:13:41 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/27 14:29:41 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	create_point(int x, int y, int z)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

t_ppoint	project_point(t_point point)
{
	t_ppoint	p_point;

	p_point.x = point.x * cos(ANGLE) + point.y * cos(ANGLE + 2) + point.z * cos(ANGLE - 2) + WIDTH / 2;
	p_point.y = point.x * sin(ANGLE) + point.y * sin(ANGLE + 2) + point.z * sin(ANGLE - 2) + HEIGHT / 2;
	return (p_point);
}

int	open_map(char map_filename[])
{
	int	map_fd;

	map_fd = open(map_filename, O_RDONLY);
	if (map_fd < 0)
		perror(map_filename);
	return (map_fd);
}

void	read_map(t_map *map, int map_fd)
{
	char	*line;
	int		col;
	int		row;

	row = 0;
	line = get_next_line(map_fd);
	if (!line)
		invalid_map(map);
	map->len = count_words(line, ' ');
	while (line)
	{
		if ((int)count_words(line, ' ') != map->len)
			invalid_map(map);
		map->height = row + 1;
		col = -1;
		while (++col < map->len)
		{
			if ((row * map->len + col) >= (int)map->capacity)
				double_array_size(map);
			map->map[(row * map->len + col)] = create_point(TILE_WIDTH * col, TILE_HEIGHT * row,  get_value(line, col));
		}
		free(line);
		++row;
		line = get_next_line(map_fd);
	}
}

int	count_words(char *s, char sep)
{
	int	size;
	int	i;
	int	is_first_char;

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
