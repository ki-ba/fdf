/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:13:41 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/14 14:26:13 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

static size_t	count_words(char *s, char sep)
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

int	check_arg(char *str)
{
	char	*dot_ptr;

	if (!str)
		return (1);
	dot_ptr = ft_strrchr(str, '.');
	if (!dot_ptr)
		return (1);
	return (*(dot_ptr + 4) != '\0' || ft_strlen(str) <= 4);
}

int	open_map(char map_filename[])
{
	int	map_fd;

	map_fd = open(map_filename, O_RDONLY);
	if (map_fd < 0)
		perror(map_filename);
	return (map_fd);
}

void	read_map(t_vars *vars)
{
	char	*line;
	size_t	col;
	size_t	row;
	t_map	*map;

	map = vars->scene->map;
	row = 0;
	line = get_next_line(vars->map_fd);
	if (!line)
		invalid_map(vars, NULL);
	init_map(vars, count_words(line, ' '));
	while (line)
	{
		if (count_words(line, ' ') != map->len)
			invalid_map(vars, line);
		if ((row + 1) > map->h_capacity)
			double_array_size(vars);
		map->height = row + 1;
		col = -1;
		while (++col < map->len)
			map->map[row][col] = create_point(col, row, get_value(line, col));
		free(line);
		++row;
		line = get_next_line(vars->map_fd);
	}
}
