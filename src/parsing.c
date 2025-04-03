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
#include "libft.h"

void	create_point(t_matrix *point, double x, double y, double z)
{
	double		values[3];

	values[0] = x;
	values[1] = y;
	values[2] = z;
	create_matrix(point, 1, 3, values);
	/*printf("created point %f, %f, %f\n", point->m[0][0], point->m[0][1], point->m[0][2]);*/
}

/*t_matrix	project_point(t_matrix point)*/
/*{*/
/*	t_matrix	p_point;*/
/**/
/*	p_point.m[X] = point.m[X] * cos(ANGLE) + point.m[Y] * cos(ANGLE + 2) + point.m[Z] * cos(ANGLE - 2);*/
/*	p_point.m[Y] = point.m[X] * sin(ANGLE) + point.m[Y] * sin(ANGLE + 2) + point.m[Z] * sin(ANGLE - 2);*/
/*	p_point.m[Z] = point.m[Z];*/
/*	return (p_point);*/
/*}*/

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
	size_t	col;
	size_t	row;

	row = 0;
	line = get_next_line(map_fd);
	if (!line)
		invalid_map(map);
	map->len = count_words(line, ' ');
	while (line)
	{
		if (count_words(line, ' ') != map->len)
			invalid_map(map);
		map->height = row + 1;
		col = -1;
		while (++col < map->len)
		{
			if ((row * map->len + col) >= map->capacity)
				double_array_size(map);
			create_point(&map->map[(row * map->len + col)], col, row, get_value(line, col));
			ft_printf("%d, %d, %d\n", col, row, get_value(line, col));
		}
		free(line);
		++row;
		line = get_next_line(map_fd);
	}
}

size_t	count_words(char *s, char sep)
{
	size_t	size;
	size_t	i;
	size_t	is_first_char;

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
