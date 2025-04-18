/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:13:41 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/16 18:42:29 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

size_t	count_words(char *s, char sep)
{
	size_t	size;
	int		i;

	i = 0;
	size = 0;
	while (s[i] && s[i] != '\n')
	{
		if (ft_is_in(s[i], "0123456789ABCDEF-,"))
		{
			++size;
			while (s[i] && s[i] != sep)
				++i;
		}
		while (s[i] && !ft_is_in(s[i], "0123456789ABCDEF-,"))
			++i;
	}
	return (size);
}

/*
	* @brief checks wether given string is of type "foo.fdf".
	* @brief ".fdf" is considered incorrect.
*/
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

/*
	* @brief opens file of given filename. Prints an error if opening
	* @brief failed. On success, return obtained fd.
*/
int	open_map(char map_filename[])
{
	int	map_fd;

	map_fd = open(map_filename, O_RDONLY);
	if (map_fd < 0)
		perror(map_filename);
	return (map_fd);
}

/*
	* @brief populates a given line of the map array with values from
	* @brief the provided array of strings.
	* @param row the number of line to populate (i.e the ordinate of
	* @param row the points to be read).
	* @param split the "numbers" to get in the map, as strings in an
	* @param split an array.
*/
void	populate_line(t_vars *vars, char **split, size_t row)
{
	size_t	col;
	int		color;
	char	*color_s;
	t_point	**map;

	if (!split)
		free_exit(vars, EXIT_FAILURE);
	map = vars->scene->map->map;
	col = 0;
	while (col < vars->scene->map->len)
	{
		color = 0;
		color_s = NULL;
		color_s = ft_strnstr(split[col], ",", vars->scene->map->len);
		if (color)
			color = ft_atoi_base(color_s + 3, "0123456789ABCDEF");
		map[row][col] = create_point(col, row, ft_atoi(split[col]), color);
		++col;
	}
	ft_free_arr(split);
}

/*
	* @brief populates the map array with values from the map file.
	* @brief the map array grows as necessary by doubling its size
	* @brief when needed.
*/
void	read_map(t_vars *vars)
{
	char	*line;
	size_t	row;
	t_map	*map;

	map = vars->scene->map;
	row = 0;
	line = get_next_line(vars->map_fd);
	if (!line)
		invalid_map(vars, NULL);
	init_map(vars, line);
	while (line)
	{
		if (count_words(line, ' ') != map->len)
			invalid_map(vars, line);
		if ((row + 1) > map->h_capacity)
			double_array_size(vars);
		map->height = row + 1;
		populate_line(vars, ft_split(line, ' '), row);
		free(line);
		++row;
		line = get_next_line(vars->map_fd);
	}
}
